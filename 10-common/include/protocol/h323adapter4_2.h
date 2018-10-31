/*****************************************************************************
   ģ����      : H323Adapter
   �ļ���      : H323Adapter.h
   ����ļ�    : H323Adapter.cpp
   �ļ�ʵ�ֹ���: ���ϲ�Ӧ���ṩAPI�����ͻص�����ԭ��
   ����        : �˻�
   �汾        : V3.0  Copyright(C) 2003 KDC, All rights reserved.
-----------------------------------------------------------------------------
   �޸ļ�¼:
   ��  ��      �汾        �޸���      �޸�����
   2003/07/25  3.0         ��  ��      ����
   2004/07/19  3.1         κ�α�      �����Ż�
******************************************************************************/

#ifndef _H323ADAPTER_H
#define _H323ADAPTER_H

#include "osp.h"
//add by yy for ipv6
#include "rvaddress.h"
//#define RV_H323_TRANSPORT_ADDRESS RV_H323_TRANSPORT_ADDRESS_ANY
//end
#include "cm.h"
#include <time.h>
#include <math.h>


#ifdef WIN32
#define KDVCALLBACK CALLBACK
#else
#define KDVCALLBACK
#endif

#ifndef IN
#define IN
#endif//!IN
#ifndef OUT
#define OUT
#endif//!OUT

#ifdef _LINUX_
#include <stdarg.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

#ifndef min
#define min(a,b) ((a)>(b)?(b):(a))
#endif
#ifndef max
#define max(a,b) ((a)>(b)?(a):(b))
#endif

#endif//!_LINUX_

///////////////////////////////// KDV H323 Э��汾�� ///////////////////////////////
// ���� TH323CONFIG.SetVersionId
//

#define KDVH323_VERID      (u8*)"8"

#define LEN_KDVH323_VERID  strlen((s8*)KDVH323_VERID)
//
////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////// ���Ժ��� ///////////////////////////////
API void kdv323adptver();
API void kdv323adpthelp();
API void pne();
API void set323trace( IN u8 byLevel);
API void setstacklog( IN s32 nLevel = 0, IN BOOL bFileLogOn = FALSE);
API void kdv323help();
API void radvaltree();//[20120619]
API void radallnode( IN BOOL bJustRootNode = TRUE );//[20120918]

///////////////////////////////// ���ȶ��� ///////////////////////////////
#define LEN_TERID			(u16)128				//�ն�������󳤶�
#define LEN_GUID			(u8)16					//GIUD����
#define LEN_H245_CONFID		(u16)32					//H245����ID 
#define LEN_CONFNAME		(u16)256				//h323-id
#define LEN_NETADDR			sizeof(TNETADDR)		//��·��ַ����
#define LEN_MTNUM_PERCONF	(u16)193				//ÿ�������е���������
#define LEN_OID				(u16)16					//OID����
#define LEN_CALLADDR		sizeof(TAliasAddr)		//���е�ַ����
#define LEN_CHANPARAM		sizeof(TCHANPARAM)		//�ŵ���������
#define LEN_TERINFO			sizeof(TTERINFO)		//�ն���Ϣ����
#define LEN_CAP				sizeof(TCapSet)			//������������
#define LEN_H243PWD			(u16)32                 //���볤��
#define LEN_ALIAS			(u16)64				    //����������h323-id
#define LEN_DHKEY_MAX		(u16)256                //dhkey����󳤶�
#define LEN_DH_X			(u16)8                  //dh�е����������
#define LEN_DHKEY			(u16)64                 //dhkey�ĳ���
#define LEN_H235KEY_MAX		(u16)64					//(1-65535)  
#define LEN_DISPLAY_MAX		(u16)82                 //��ʾ��Ϣ����󳤶�
#define LEN_DISPLAY_MIN		(u16)2                  //��ʾ��Ϣ����С����
#define MAX_CONF_NUM		(u16)32                 //��������. Jacky Wei, changed from 32 to 24 to solve cmEvFacility lost issue(Bug00156267)
#define ANNEXQ_DYNAMIC_PT	(u16)100				//h.281��̬�غ�
#define LEN_USERINFO_MAX    (u8)131					//UserInfor����󳤶�
#define LEN_USERINFO_MIN	(u16)2                  //UserInfor����С����
#define MAX_CAPTABLE_SIZE	(u16)64					//max 256
#define MAX_ALTCAP_NUM      MAX_CAPTABLE_SIZE		//max 256
#define MAX_SIMUCAP_NUM     (u16)16					//max 256 (CodianΪ13)
#define MAX_DESCAP_NUM      (u16)5					//max 256 (ץ�����ֶ���1��������2����)
#define MAX_H264CAP_NUM     (u8)10                  //H.264��������
#define MAXBITRATE_H261     (u16)19200				//��λ100bps
#define MAXBITRATE_H263     (u32)192400				//��λ100bps
#define CALLPORT			(u16)1720				//���ж˿�
#define RASPORT				(u16)1719				//RAS�˿� 
#define MAXALIASNUM			(u16)128				//��������
#define MAXSessionDescript	(u8)128                 //֧�ֵ����SessionDescript
#define MAX_ProductIDSize	(u16)256                //��Ʒ��Ϣ����󳤶�
#define MAX_VersionIdSize	(u16)256                //�汾��Ϣ����󳤶�
#define MAX_LEN_CONFNAME    (u16)64					//����������󳤶�
#define PRODUCTSTRING_LESS_SIZE        (u16)32      //��Ʒ��Ϣ�ĳ���,���ڻ�ȡ�Է��Ĳ�Ʒ��Ϣ
#define VERSIONSTRING_LESS_SIZE        (u16)32      //�汾��Ϣ�ĳ���,���ڻ�ȡ�Է��İ汾��Ϣ
#define LEN_NONSTANDARD_MAX (u16)2048               //setup��Ϣ�зǱ����ݵ���󳤶�
#define LEN_DES_KEY         (u8)8                   //DES����Կ����
#define LEN_AES_KEY         (u8)16                  //AES����Կ����
#define MAX_CALL_NUM        (u16)256
#define MIN_CALL_NUM        (u16)10
#define MAX_CHANNEL_NUM     (u16)20
#define MIN_CHANNEL_NUM     (u16)12
#define RequestMsg_BGN		(u16)101
#define RequestMsg_END		(u16)300
#define ResponseMsg_BGN		(u16)301
#define ResponseMsg_END		(u16)500
#define CommandMsg_BGN		(u16)501
#define CommandMsg_END		(u16)700
#define IndicationMsg_BGN	(u16)701
#define IndicationMsg_END	(u16)900
#define LEN_256				(u16)256
#define LEN_1				(u16)1
#define LEN_128				(u16)128
#define REG_NAME_LEN		(u16)64
#define REG_PWD_LEN			(u16)64
#define VALID_LEN_ALIAS      (u16)16   //��Ч��������  
//add by yj for ipv6
#define IPV6_NAME_LEN		(u16)64  //IPv6��ַ������
#define INVALID_NODEID      RV_PVT_INVALID_NODEID
#define TYPE_NONE           RV_ADDRESS_TYPE_NONE         //��ʾΪδ�����ַ
#define TYPE_IPV4           RV_ADDRESS_TYPE_IPV4         //��ʾ֧��IPv4��ַ
#define TYPE_IPV6           RV_ADDRESS_TYPE_IPV6         //��ʾ֧��IPv6��ַ
//#define TYPE_SCTP           RV_NET_SCTP         //��ʾͬ��֧��IPv4��IPv6��ַ
//end
       


#define FLAG_H460FEATURESIGNALL			18			//460.18
#define FLAG_H460MEDIAFWSIGNALL			19			//460.19     

#define FLAG_H460SUPPORTMULTIPLEXDMEDIA	1			//֧�ֶ˿ڸ���
#define FLAG_H460MEDIATRAVESALSERVER	2			//����Ϊ460������

///////////////////////////////// ��Ϣ���� ///////////////////////////////

//������Ϣ
enum H225CallMsgType 
{
	h_call_invalidInterface = 0,
    h_call_make,		            //�������	      [outgoing]: TCALLPARAM
	h_call_incoming,		        //���е���		  [incoming]: TCALLPARAM + VendorProductId		  	  	
	h_call_answer,		            //����(�ܾ�)����  [outgoing]: TNODEINFO
	h_call_drop,                    //��������		  [outgoing]: 1 byte,reason
	h_call_connected,               //���н���		  [incoming]: TNODEINFO	
	h_call_disconnected,            //���жϿ�		  [incoming]: 1 byte,reason	
	h_call_facility,			    //������չ����	  [incoming]&[outgoing]: TFACILITYINFO   
	h_call_h460make,		        //����h460����	  [outgoing]: TH460CALLPARAM
	//add by daiqing 20100723 for 460 kdv
	h_call_h460CallerMake,			//�����ն��յ�facility������� [outgoing]: TCALLPARAM
	//end
    //Jacky Wei add h_call_alerting event for KDV1000
    h_call_alerting,                //Useless except for KDV1000 processes
};

//RAS��Ϣ
enum H225RasMsgType 
{
	h_ras_invalidInterface = 0,
	h_ras_GRQ,						//reserve
	h_ras_GCF,						//reserve
	h_ras_GRJ,						//reserve
	h_ras_RRQ,                      //[incoming]&[outgoing]:[TRRQINFO]
	h_ras_RCF,						//[incoming]&[outgoing]:[TRCFINFO]    
	h_ras_RRJ,                      //[incoming]&[outgoing]:[int:reason]
	h_ras_LWRRQ,                    //[incoming]&[outgoing]:[TRRQINFO]
	h_ras_ARQ,						//[incoming]&[outgoing]:[HCALL][TARQINFO]
	h_ras_ACF,                      //[incoming]&[outgoing]:[HCALL][TACFINFO]
	h_ras_ARJ,                      //[incoming]&[outgoing]:[HCALL][int:reason]
	h_ras_DRQ,                      //[incoming]&[outgoing]:[HCALL][TDRQINFO]
	h_ras_DCF,						//[incoming]&[outgoing]:[HCALL][TDCFINFO]
	h_ras_DRJ,						//[incoming]&[outgoing]:[HCALL][int:reason]
	h_ras_URQ,						//[incoming]&[outgoing]:[TURQINFO]
	h_ras_UCF,						//[incoming]&[outgoing]:[TUCFINFO]
	h_ras_URJ,						//[incoming]&[outgoing]:[int:reason]
	h_ras_IRQ,                      //[incoming]&[outgoing]:[HCALL][TIRQINFO]
	h_ras_IRQTimeOut,               //[incoming]:           [HCALL]
	h_ras_IRR,						//[incoming]&[outgoing]:[HCALL][TIRRINFO]
	h_ras_BRQ,						//[incoming]&[outgoing]:[HCALL][TBRQINFO] 
	h_ras_BCF,                      //[incoming]&[outgoing]:[HCALL][TBCFINFO]
	h_ras_BRJ,						//[incoming]&[outgoing]:[HCALL][int:reason]
	h_ras_LRQ,						//[incoming]&[outgoing]:[TLRQINFO]
	h_ras_LCF,                      //[incoming]&[outgoing]:[TLCFINFO]
	h_ras_LRJ,                      //[incoming]&[outgoing]:[int:reason]

	h_ras_registration,				//�Զ�RAS�޸�ע����Ϣ������GKע��	[outgoing]:TRRQINFO
	h_ras_unregistration,			//�Զ�RAS��GKע��				    [outgoing]:NULL
	h_ras_online,					//�Զ�RAS��GKע��ɹ�			    [incoming]:NULL
	h_ras_offline,					//�Զ�RASδ��GKע��			        [incoming]:NULL

	h_ras_NSM,                      //�Ǳ���Ϣ
	//add by daiqing 20100720 for 460
	h_ras_SCI,                      //[incoming]&[outgoing]:[TSCIINFO]
	h_ras_SCR,                      //[incoming]&[outgoing]:[s32]

	h_ras_manual_NSM,				//�ֶ�RAS �Ǳ���Ϣ [20121018]
	
};

//�߼�ͨ����Ϣ
enum H245ChanMsgType 
{
	h_chan_invalidInterface = 0,
    h_chan_open,						//[incoming]&[outgoing]: [NULL]&[TCHANPARAM] ���߼�ͨ��
	h_chan_openAck,						//[incoming]           : [TCHANPARAM]        ͬ����߼�ͨ��
	h_chan_openReject,					//[outgoing]           : [emlogChannelRejectCause]     �ܾ����߼�ͨ��
	h_chan_connected,					//[incoming]           : NULL                �ŵ��ѽ���
	h_chan_close,						//[outgoing][incoming] : NULL                �ر��߼�ͨ��	

	h_chan_parameter,					//[incoming]	       : [TCHANPARAM]        �õ��߼��ŵ�ý������������ŵ���ַ
	h_chan_remoteRtpAddress,			//[incoming]           : [TNETADDR]          �õ��Զ�RTP��ַ 
	h_chan_remoteRtcpAddress,			//[incoming]           : [TNETADDR]          �õ��Զ�RTCP��ַ
	h_chan_dynamicpayloadtype,			//[incoming]           : [u8]                �õ�ͨ���Ķ�̬�غ�����    
	h_chan_VideoFreezePicture,			//[incoming]&[outgoing]: [NULL]&[NULL]       ͼ�񶳽�����
	h_chan_videofastupdatePIC,			//[incoming]&[outgoing]: [NULL]&[NULL]       ͼ���������
	h_chan_videofastupdateGOB,			//[incoming]&[outgoing]: [TVFUGOB]&[TVFUGOB] GOB��������
	h_chan_videofastupdateMB,			//[incoming]&[outgoing]: [TVFUMB]&[TVFUMB]   MB��������
	h_chan_VideoSendSyncEveryGOB,		//[incoming]&[outgoing]: [NULL]&[NULL]       use sync for every GOB as defined in H.263
	h_chan_VideoSendSyncEveryGOBCancel, //[incoming]&[outgoing]: [NULL]&[NULL]       cancel use sync for every GOB as defined in H.263
    h_chan_SwitchReceiveMediaOn,        //[incoming]&[outgoing]: [NULL]&[NULL]       logical channel should be used for receive
	h_chan_SwitchReceiveMediaOff,       //[incoming]&[outgoing]: [NULL]&[NULL]       logical channel should not be used for receive
	h_chan_tsto,						//[incoming]&[outgoing]: [TTSTO]             temporal spatial tradeoff operation.
	h_chan_flowControl,					//[incoming]&[outgoing]: [u16:rate(kbps)]    ������������

	h_chan_on,							//[incoming]&[outgoing]: [NULL]&[NULL]       �����߼�ͨ����    ��ʼ��������    
	h_chan_off,							//[incoming]&[outgoing]: [NULL]&[NULL]       �����߼�ͨ����    ֹͣ��������

	h_chan_MediaLoopRequest,			//[incoming]: [HCHAN]
	h_chan_MediaLoopConfirm,			//[incoming]: [HCHAN]
	h_chan_MediaLoopReject,				//[incoming]: [HCHAN]
	h_chan_MediaLoopOff,				//[incoming]: [HCALL]
	h_chan_EncryptSyn,                  //[incoming]: [TEncryptSync]
	h_chan_EncryptionUpdateRequest,     //[incoming]: [HCHAN]
	h_chan_EncryptionUpdateCommand,     //[incoming]: [HCHAN][TEncryptSync]

    h_chan_flowControlIndication,   	//[incoming]&[outgoing]: [u16:rate(kbps)]    ��������ָʾ
	h_chan_keepAliveAddress,			//[incoming]           : [TNETADDR]          �õ��Զ�keepAlive��ַadded by wangxiaoyi for h460 keepalivechannel
	h_chan_newchan,							  //[incoming]           : [HCHAN]          OnNewChan����Ϣ
    
};


/*
 H245 message
 0. h_ctrl_h245TransportConnected��ʾh245��·�Ľ��������յ�������Ϣǰ���÷����κ�H245��Ϣ��
 1. ������(capset)���������Ӿ���(MSD)��h_ctrl_h245TransportConnected�󷢳����ϲ���뷢����������Ϣ��
 2. ˫�����������������Ӿ�������ɺ󣬲Ż��յ�h_ctrl_h245Established��Ϣ��
 3. ���Ӿ����ж���Э��ջ����ֻ���ڱ��˻�û�з������Ӿ�����Ϣʱ��Э��ջ�Żᱨ��Է������Ӿ���request����h_ctrl_masterSlaveDetermine
 4. ��ͨ����Ϣ�������յ�h_ctrl_h245Established����ܷ��͡�
*/


//���������Ϣ
enum H245CtrlMsgType 
{
	h_ctrl_invlaidInterface = 0,
	h_ctrl_h245TransportConnected,          //[incoming]	       :[NULL]	       h245ͨ���ոս���, ��ʱ���Կ�ʼ��������������ȷ��
	h_ctrl_h245Established,                 //[incoming]		   :[NULL]		   ��������������ȷ�����,���Կ�ʼ���߼�ͨ�����յ�CancelMultipointConference Ҳ�ᷢ����Ϣ 
	h_ctrl_masterSlave,						//[incoming]		   :[u8:result]	   ���Ӿ���ack, [incoming]--result��ʾ�������� 
	h_ctrl_masterSlaveDetermine,            //[outgoing]&[incoming]:[s32[2]]       ���Ӿ���request, 4byte(terminal Type�� 50��240) + (optional)4 bytes(random number 0-0xffffff), 
	h_ctrl_capNotifyExt,                    //[incoming]&[outgoing]:[TCapSet]&[TCapSet]  �Զ�����ָʾ
	h_ctrl_capResponse,						//[incoming]&[outgoing]:[u8: result]         ��������Ӧ
//7
	/************************h.245 Standard**************************/
	h_ctrl_MultipointConference,            //��ʼ������ָʾ  MC->ter, Master->slave,   [incoming]&[outgoing]: NULL
	h_ctrl_CancelMultipointConference,      //ȡ��������ָʾ  MC->ter, Master->slave,   [outgoing]: NULL

	h_ctrl_communicationModeCommand,        //����ģʽ����	    MC->ter,   [incoming]&[outgoing]: [TCOMMODEINFO[]],Ŀǰ��ʹ��
//10	
	h_ctrl_enterH243Password,				//MCѯ�ʻ�������    MC->ter,   [incoming]&[outgoing]: NULL
	h_ctrl_passwordResponse,				//�ն˻ش�����	    ter->MC,   [incoming]&[outgoing]: [TPassRsp]
	h_ctrl_terminalNumberAssign,            //�����ն˱��	    MC->ter,   [incoming]&[outgoing]: [TTERLABEL]
	h_ctrl_terminalListRequest,             //�����ն��б�	    ter->MC,   [incoming]&[outgoing]: NULL			
	h_ctrl_terminalListResponse,            //�ش��ն��б�	    MC->ter,   [incoming]&[outgoing]: [TTERLABEL[]]
	h_ctrl_requestTerminalID,               //terѯ���ն���	    ter->MC,   [incoming]&[outgoing]: [TTERLABEL]
	h_ctrl_mCTerminalIDResponse,            //MC�ش��ն���	    MC->ter,   [incoming]&[outgoing]: [TTERINFO]
	h_ctrl_enterH243TerminalID,				//MCѯ���ն���	    MC->ter,   [incoming]&[outgoing]: NULL
	h_ctrl_terminalIDResponse,              //ter�ش��ն���	    ter->MC,   [incoming]&[outgoing]: [TTERINFO]
	h_ctrl_requestAllTerminalIDs,           //ter���������ն��� ter->MC,   [incoming]&[outgoing]: NULL
	h_ctrl_requestAllTerminalIDsResponse,   //�ش������ն�����	MC->ter,   [incoming]&[outgoing]: [TTERINFO[]]
	h_ctrl_terminalJoinedConference,        //�ն˼������		MC->ter,   [incoming]&[outgoing]: [TTERLABEL]
	h_ctrl_terminalLeftConference,          //�ն��˳�����		MC->ter,   [incoming]&[outgoing]: [TTERLABEL]
	h_ctrl_dropTerminal,                    //ǿ���ն��˳�		chair->MC, [incoming]&[outgoing]: [TTERLABEL]
	h_ctrl_terminalDropReject,              //ǿ���ն��˳�ʧ��	MC->chair, [incoming]&[outgoing]: NULL	
	h_ctrl_dropConference,                  //�������� chair->MC,MC->ter,  [incoming]&[outgoing]: NULL
//26
	h_ctrl_requestForFloor,                 //���뷢��			ter->MC,   [incoming]&[outgoing]: NULL
	h_ctrl_floorRequested,                  //��������			MC->chair, [incoming]&[outgoing]: [TTERLABEL]
	h_ctrl_makeTerminalBroadcaster,         //�㲥�ն�			chair->MC, [incoming]&[outgoing]: [TTERLABEL+u8:CtrlMode]
	h_ctrl_makeTerminalBroadcasterResponse, //�㲥Ӧ��			MC->chair, [incoming]&[outgoing]: [u8:CtrlResult]
	h_ctrl_cancelMakeTerminalBroadcaster,   //ȡ���㲥			chair->MC, [incoming]&[outgoing]: NULL
	h_ctrl_seenByAll,                       //�㲥Դָʾ		MC->ter,   [incoming]&[outgoing]: NULL
	h_ctrl_cancelSeenByAll,                 //�㲥Դ��ȡ��ָʾ	MC->ter,   [incoming]&[outgoing]: NULL
	h_ctrl_seenByAtLeastOneOther,           //��֪�������ն�ѡ��  MC->ter, [incoming]&[outgoing]: NULL
	h_ctrl_cancelSeenByAtLeastOneOther,     //��֪�������ն�ͣ��  MC->ter, [incoming]&[outgoing]: NULL
	h_ctrl_sendThisSource,                  //ѡ���ն�			chair->MC, [incoming]&[outgoing]: [TTERLABEL+u8:CtrlMode]
	h_ctrl_sendThisSourceResponse,          //ѡ��Ӧ��			MC->chair, [incoming]&[outgoing]: [u8:CtrlResult]
	h_ctrl_cancelSendThisSource,            //ȡ��ѡ��			chair->MC, [incoming]&[outgoing]: NULL
	h_ctrl_terminalYouAreSeeing,            //���ڹۿ�����ƵԴ	MC->ter,   [incoming]&[outgoing]: [TTERLABEL]
//39
	h_ctrl_makeMeChair,                     //������ϯ			ter->MC,   [incoming]&[outgoing]: NULL
	h_ctrl_cancelMakeMeChair,               //�ͷ���ϯ			chair->MC, [incoming]&[outgoing]: NULL
	h_ctrl_makeMeChairResponse,             //��ϯ����/�ͷ�Ӧ��	MC->ter,   [incoming]&[outgoing]: [u8:CtrlResult]
	h_ctrl_withdrawChairToken,              //��ϯ����ָʾ		MC->ter,   [incoming]&[outgoing]: NULL
	h_ctrl_requestChairTokenOwner,          //ѯ�ʵ�ǰ��ϯ		ter->MC,   [incoming]&[outgoing]: NULL
	h_ctrl_chairTokenOwnerResponse,         //�ش�ǰ��ϯ		MC->ter,   [incoming]&[outgoing]: [TTERINFO]
	h_ctrl_mcLocationIndication,			//����MC��ʵ���ַ	MC->ter,   [incoming]&[outgoing]: [TNETADDR]
    h_ctrl_roundTripDelay,					//���Զ��Ƿ�Alive ter->MC,MC->ter, [incoming]&[outgoing]: [s32:nMaxDelay]
//47   
    h_ctrl_H239Message,                     //����H239��Ϣ      ter->MC,MC->ter, [incoming]&[outgoing]: [TH239INFO]
    h_ctrl_userInput,                       //����UserInput��Ϣ            [incoming]&[outgoing]: [TUserInputInfo]

    h_ctrl_roundTripDelay_request,          //h_ctrl_roundTripDelay����ĸ�����Ϣ(����ǽ�ڲ�ʹ�ã��������������Ӧ��)

	h_ctrl_customFecc,						//FECC��Ϣ��ʹ��H245����FECC��Ϣ�Ĵ��ݣ���Ҫ����pxy��

    h_ctrl_multiplexCapability,             //multiplexCapability��Ϣ,  [incoming]&[outgoing]: [TMultiplexCapability]
	
	h_ctrl_masterSlaveResponse,             //[outgoing]                           ���Ӿ���response�������յ��Է�masterslaveresquest���ֶ��ظ��Է�ack
	h_ctrl_OutgoingMultipointConference,	//[outgoing]		ת��h_ctrl_MultipointConference��Ϣ���������ر�


	h_ctrl_standardend              = 100,
	
	h_ctrl_mcuvccommonnonstandstart = 101,  //MCU��Ʒ�Զ������Ϣ 12 Januaray 2011
	h_ctrl_chairTransferReq,				//��ϯ�ն�ת����������	chair->MC, TTERLABEL
	h_ctrl_chairInviteTerminalReq,			//��ϯ�����ն�����		chair->MC, TTERADDR
	h_ctrl_terStatusReq,					//�ն�״̬����			MC->ter,   NULL
	h_ctrl_pollParamReq,					//��ѯ��ѯ����			MC->ter,   NULL	
	h_ctrl_whoViewThisTerReq,				//ѯ��MCU A�ն˱�˭ѡ��	ter->MC,   TTERLABEL(A)
	h_ctrl_confInfoReq,						//ѯ�ʻ�����Ϣ			ter->MC,   NULL
	h_ctrl_delayConfTimeReq,				//�ӳ�����ʱ��			chair->MC, u16, minutes
	h_ctrl_letTerViewMeReq,					//ǿ��ѡ������			ter->MC,   TTERLABEL(��ǿ��ѡ����) + 1BYTE(DataType) 
	h_ctrl_multicastTerReq,					//�鲥�ն�����			ter->MC,   TTERLABEL(Ŀ���ն�)	
	h_ctrl_destterStatusReq,                //Դ�ն�����Ŀ���ն�״̬     ter->MC,TTERLABEL(Ŀ���ն�)��

	h_ctrl_whoViewThisTerRsp,				//��ӦwhoViewThisTerReq	MC->ter, TTERLABEL(��ѡ���ն�) + 1Byte(ѡ���ն˸���) + TTERLABEL����
	h_ctrl_pollParamRsp,					//��ѯ����Ӧ��			ter->MC,  
	                                        //����(1Byte,PollType) + ģʽ(1Byte,DataType) + ��ǰ״̬(1Byte, PollStatus)
											//+ ��ǰ��ѯ�����ն�(TTERLABEL��+ ʱ����(u16,s). ���û����ȫ��0)
											//�ն˸���(1Byte) + �б�(TTERLABEL���� + ʱ����(1Byte,s))

											//����(1Byte,PollType) + ģʽ(1Byte,DataType) + ʱ����(1Byte,s) + �ն˸���(1Byte) + �б�(TTERLABEL����)
	h_ctrl_confInfoRsp,						//�ش������Ϣ			MC->ter, ͸��ת����MTC
	h_ctrl_delayConfTimeRsp,				//�ӳ�����ʱ��Ӧ��		1BYTE,granted/denied
	h_ctrl_letTerViewMeRsp,					//ǿ��ѡ��Ӧ��			MC->ter,   1BYTE(granted/denied)
	
	h_ctrl_startVACReq,						//��ʼ������������ chair->MC, NULL
	h_ctrl_stopVACReq,						//ֹͣ������������ chair->MC, NULL
	h_ctrl_startVACRsp,						//��ʼ��������������Ӧ MC->ter, 1BYTE(granted/denied)
	h_ctrl_stopVACRsp,						//ֹͣ��������������Ӧ MC->ter,1BYTE(granted/denied)

	h_ctrl_startDiscussReq,					//��ʼ���� chair->MC, 1byte(ͬʱ�μ�����(����)�ĳ�Ա����)
	h_ctrl_stopDiscussReq,					//ֹͣ���� chair->MC, NULL
	h_ctrl_startDiscussRsp,					//��ʼ����������Ӧ MC->ter,1BYTE(granted/denied)
	h_ctrl_stopDiscussRsp,					//ֹͣ����������Ӧ MC->ter,1BYTE(granted/denied)
	
	h_ctrl_startVMPReq,						//��ʼ��Ƶ���� chair->MC, struct TVMPParam
	h_ctrl_stopVMPReq,						//ֹͣ��Ƶ���� chair->MC, NULL
	h_ctrl_changeVMPParamReq,				//�ı���Ƶ���ϲ��� chair->MC, struct TVMPParam
	h_ctrl_getVMPParamReq,					//�õ���Ƶ���ϲ��� chair->MC, NULL
	h_ctrl_startVMPRsp,						//��ʼ��Ƶ����������Ӧ MC->ter,1BYTE(granted/denied)
	h_ctrl_stopVMPRsp,						//ֹͣ��Ƶ����������Ӧ MC->ter,1BYTE(granted/denied)
	h_ctrl_changeVMPParamRsp,				//�ı���Ƶ���ϲ���������Ӧ MC->ter,1BYTE(granted/denied)
	h_ctrl_getVMPParamRsp,					//�õ���Ƶ���ϲ���������Ӧ MC->ter,struct TVMPParam
	
	h_ctrl_multicastTerRsp,					//�鲥�ն�Ӧ��   MC->ter,  TTERLABEL(Ŀ���ն�) + u32(ip,���ʧ��ipΪ0) 
											//                       + u16(��Ƶ�˿ں�)     + u16(��Ƶ�˿ں�)
											//                       + u8(��Ƶ��ʵ�غ�ֵ)  + u8(��Ƶ��ʵ�غ�ֵ)
											//                       + u8(��Ƶ��������)    + u8(��Ƶ��������) -- emEncryptTypeNone��
											//                       + TEncryptSync(��Ƶ������Ϣ) + TEncryptSync(��Ƶ������Ϣ)
	
	h_ctrl_destterStatusRsp,                //����Ŀ���ն�״̬����Ӧ   MC->ter,TTERLABEL(Ŀ���ն�) + _TTERSTATUS

	h_ctrl_makeTerQuietCmd,					//Զ�˾�������			ter->MC,MC->ter,  TTERLABEL(dst) + 1BYTE(turn_on/turn_off)
	h_ctrl_makeTerMuteCmd,					//Զ����������			ter->MC,MC->ter,  TTERLABEL(dst) + 1BYTE(turn_on/turn_off)
	h_ctrl_startPollCmd,					//��ʼ��ѯ����			MC->ter,    
											//����(1Byte,PollType) + ģʽ(1Byte,DataType) + �ն˸���(1Byte) + �б�(TTERLABEL���� + ʱ����(1Byte,s))
	h_ctrl_stopPollCmd,		   				//ֹͣ��ѯ����			MC->ter,	NULL
	h_ctrl_pausePollCmd,					//��ͣ��ѯ				MC->ter,	NULL
	h_ctrl_resumePollCmd,					//�ָ���ѯ				MC->ter,	NULL
											//						action(1Byte,������ͨ����:turn_on(��ʼ)/turn_off(ֹͣ);����Ԥ������:�����1-4��ʾԤ��λ)
	h_ctrl_stopViewMeCmd,					//ֹͣǿ��ѡ��			ter->MC
	h_ctrl_stopMulticastTer,				//ֹͣ�鲥�ն�			ter->MC,	TTERLABEL
	
    h_ctrl_matrixCfgCmd,                    //Ϊ����3.6�ն˱���, ������������			MC->ter,	1Byte(MT_AUDIO/MT_VIDEO/MT_AV) + _TMATRIXPORT(Output) + _TMATRIXPORT(Input)
	
    h_ctrl_chairSelectViewCmd,				//��ϯѡ��				ter->MC,    <m,t> + 1Byte(type_audio/type_video/type_av)	

	h_ctrl_chairInviteFailedInd,			//��ϯ�����ն�ʧ��		MC->chair, TTERADDR
	h_ctrl_confWillEndInd,					//���鼴������ָʾ		MC->chair, u16 minutes, ��ʾ���ж�ý���
	h_ctrl_delayConfTimeInd,                //�ӳ�����ʱ��ָʾ      MC->ter, u16 ����
	h_ctrl_terApplyChairInd,				//���ն���Ind,					//�ն�״ָ̬ʾ			ter->MC,   _TTERSTATUS ( response h_ctrl_terStatusReq)	
	h_ctrl_terStatusInd,					//�ն�״ָ̬ʾ			ter->MC,   _TTERSTATUS ( response h_ctrl_terStatusReq)	
	h_ctrl_pollParamInd,                    //��ѯ״ָ̬ʾ          ����(1Byte,PollType) + ģʽ(1Byte,DataType) + ��ǰ״̬(1Byte, PollStatus) 
	                                        //                      + ��ǰ��ѯ�����ն�(TTERLABEL��+ ʱ����(u16,s). ���û����ȫ��0)
	h_ctrl_smsInd,							//����Ϣָʾ			ter->MC,MC->ter,TTERLABEL(src) + TTERLABEL(dst) + (1BYTE:��������)+�ַ���('\0'����)	
	h_ctrl_broadcasterTokenOwnerInd,		//�¹㲥Դͨ��			MC->ter, TTERLABEL

	h_ctrl_matrixSchemeLoadCmd,             //Ϊ����3.6�ն˱���, ���󷽰���������      MC->ter,��ָ���������õ�ǰ���� TMATRIXSCHEME�ṹ
	h_ctrl_matrixSchemeSaveCmd,             //Ϊ����3.6�ն˱���, ���󷽰���������      MC->ter,���浱ǰ����Ϊָ������ TMATRIXSCHEME�ṹ
	h_ctrl_defaultmatrixInfoCmd,            //Ϊ����3.6�ն˱���, ����Ĭ��������Ϣ����  MC->ter,1Byte(MT_AUDIO/MT_VIDEO/MT_AV)
	h_ctrl_matrixInfoInd,                   //Ϊ����3.6�ն˱���, ��ǰ����������Ϣָʾ	ter->MC,1Byte(MT_AUDIO/MT_VIDEO/MT_AV) + _TMATRIXINFO(�����AV��Ϊ����,A+V)
	
    h_ctrl_termSourceNameInd,               //�ն���ƵԴ����ָʾ    MC->ter,��Ϣ�����ַ�����'\0'����
	
    h_ctrl_matrixSchemeInd,                 //Ϊ����3.6�ն˱���, ���о��󷽰�ָʾ      ter->MC,TMATRIXSCHEME�ṹ�����飬��8�׷���
	
    h_ctrl_feccCmd,							//Զң����				ter->MC,MC->ter,  TTERLABEL(dst) + Command(1Byte,��������,FeccCommand) + 
	
    h_ctrl_matrixInfoReq,                   //Ϊ����3.6�ն˱���, �������ǰ������Ϣ	MC->ter,1Byte(MT_AUDIO/MT_VIDEO/MT_AV)
	h_ctrl_matrixSchemeReq,                 //Ϊ����3.6�ն˱���, ���о��󷽰����� MC->ter,1Byte(MT_AUDIO/MT_VIDEO/MT_AV)
	
    h_ctrl_termVideoSrcCmd,					//ѡ���ն���ƵԴ		MC->ter, 1BYTE(��ƵԴ����0:S���� 1~16:C����)

	h_ctrl_chimeInReq,						//�ն�����廰				ter->MC,		NULL
	h_ctrl_makeTerChimeInCmd,				//��ϯָ���ն˲廰			ter->MC,		TTERLABEL
	h_ctrl_chimeInInd,						//�ն˲廰״̬				MC->ter			1�ֽڣ�0: ���ڲ廰, 1: �ڲ廰��
	h_ctrl_otherTerChimeInInd,				//�����ն�����廰ָʾ		MC->chair		TTERLABEL

    // mcu
    h_ctrl_McuMcuAddMtReq,					//MCU�����¼�mcu�ϵ��ն�       Mcu->Mcu  TAddMtInfo����
    h_ctrl_McuMcuAddMtRsp,                  //MCU�����¼�mcu�ϵ��ն�Ӧ��   Mcu->Mcu  1BYTE (granted/denied)
    
    h_ctrl_McuMcuCallMtCmd,                 //MCU�����¼�mcu�ϵ��ն�       Mcu->Mcu   TMt
    h_ctrl_McuMcuCallAlertingInd,           //���ں���ͨ��                 Mcu->Mcu   TMt
    h_ctrl_McuMcuMtJoinedInd,               //���ն˼���ͨ��               Mcu->Mcu   TMt
    
    h_ctrl_McuMcuDropMtCmd,                 //mcu�Ҷ��¼�mcu�ϵ��ն�       Mcu->Mcu   TMt
    h_ctrl_McuMcuDelMtCmd,                  //mcuɾ���¼�mcu�ϵ��ն�       Mcu->Mcu   TMt
    h_ctrl_McuMcuMtDisconnectedInd,         //�ն˹Ҷ�֪ͨ                 Mcu->Mcu   TMt
    h_ctrl_McuMcuMtDeletedInd,              //�ն����ͨ��                 Mcu->Mcu   TMt
    
    h_ctrl_McuMcuGetMtListReq,              //Mcu֮������Է��ն��б�      Mcu->Mcu   Null
    h_ctrl_McuMcuGetMtListRsp,              //Mcu֮������Է��ն��б�Ӧ��  Mcu->Mcu   TMt+TmtAlias����
    h_ctrl_McuMcuConfMtInfoInd,             //�ն���Ϣ֪ͨ                 Mcu->Mcu   TConfMtInfo + TMtEx����
    
    h_ctrl_McMcuSetReverseChannelCmd,       //ָ���ش�ͨ��,��Ϣ��TMt       Mcu->Mcu   Tmt
    h_ctrl_McuMcuNewReverseChannelInd,      //�»ش�ͨ��֪ͨ               Mcu->Mcu   Tmt
    h_ctrl_McuMcuAudioInfoReq,              //������Ƶ��Ϣ                 Mcu->Mcu   Null
    h_ctrl_McuMcuAudioInfoRsp,              //������Ƶ��Ϣ��Ӧ             Mcu->Mcu   TMt����
    h_ctrl_McuMcuVideoInfoReq,              //������Ƶ��Ϣ                 Mcu->Mcu   Null
    h_ctrl_McuMcuVideoInfoRsp,              //������Ƶ��Ϣ��Ӧ             Mcu->Mcu   TMt����
    
    h_ctrl_McuMcuConfMtStatusInd,           //�ն�״̬�ϱ�                 Mcu->Mcu   TMcu+TMtStatus����
    h_ctrl_McuMcuFeccCmd,                   //����ͷԶң                   Mcu->Mcu   TMt + 1byte��Զң�������� + 1 byte: Զң����
    h_ctrl_McuMcuSendMsgInd,                //�ն˶���Ϣ֪ͨ               Mcu->Mcu   ��Ϣ�壺TMt(�ն˺�Ϊ0�㲥�������ն�)+TROLLMSG(��Ч����)
    
    h_ctrl_McuMcuNewSpeakerInd,             //�ϼ��ı䷢����֪ͨ           Mcu->Mcu   ��Ϣ�壺TMt+1byte(ý��ģʽ:��Ƶ����Ƶ������)
    
    //add by jason 2005-10-11
    h_ctrl_SimpleConfInfoInd,               //mcu֪ͨ�ն˸��»�����Ϣ      MC->ter			1�ֽڣ�0: ���ڲ廰, 1: �ڲ廰��
    
    h_ctrl_terBandWidthInd,                 //mt���շ��ʹ���֪ͨ           ter->MC      u16(���մ���������Ƶ����Ƶ��,������) + u16(���ʹ���������Ƶ����Ƶ��,������)
    h_ctrl_terBitrateInfoReq,               //mcu�����ն�����              MC->ter      ��Ϣ�壺��
    h_ctrl_terBitrateInfoRsp,               //mt���ն�����Ӧ��             ter->MC      ��Ϣ�壺_TERBITRATE

    // 4.0���þ���
	h_ctrl_matrixExGetInfoCmd,              //��ȡ�ն����þ�������

    h_ctrl_matrixExInfoInd,                 //�ն����þ�������ָʾ
	                                        //    +u8 ��������˿��� 0��ʾû�о���

    h_ctrl_matrixExSetPortCmd,              //�������þ������Ӷ˿ں�
	                                        //    +u8  (1-64 )

    h_ctrl_matrixExGetPortReq,              //�����ȡ���þ������Ӷ˿�

    h_ctrl_matrixExPortInd,                 //���þ������Ӷ˿�ָʾ
	                                        //    +u8  (1-64 )

    h_ctrl_matrixExSetPortNameCmd,          //�������þ������Ӷ˿���
	                                        //    +u8  (1-64 )
										    //    +s8[MAXLEN_MATRIXPORTNAME] 0��β���ַ��� 

    h_ctrl_matrixExPortNameInd,             //���þ���˿���ָʾ
	                                        //    +u8  (1-64 )
										    //    +s8[MAXLEN_MATRIXPORTNAME] 0��β���ַ���

    h_ctrl_matrixExGetAllPortNameCmd,       //�����ȡ���þ�������ж˿���

    h_ctrl_matrixExAllPortNameInd,          //�����ȡ���þ�������ж˿���
	                                        //    +s8[][MAXLEN_MATRIXPORTNAME]
									        //    ����0 ��ʾ����˿��� ����λ����˿��װ�
    //4.0 ���þ���
    h_ctrl_innerMatrixGetAllSchemesCmd,     /*****************<< ��ȡ���󷽰�������������  >>**************	
                                             *[��Ϣ��]		
                                             * ��   
                                             */                              
                                                                                  
    h_ctrl_innerMatrixGetAllSchemesInd,     /***************<< ��ȡ���󷽰���������ָʾ  >>****************	
                                             *[��Ϣ��]			                  
                                             *    + u8( ������ ) + ITInnerMatrixScheme[ ]
                                             */ 

    h_ctrl_innerMatrixGetOneSchemeCmd,      /**************<< ��ȡ���󷽰�һ����������  >>*****************	
                                             *[��Ϣ��]		
                                             *    + u8 ( 0 ΪĬ�Ϸ��� )       ����������( 0 - 6 )
                                             */  
                                                
                                                
    h_ctrl_innerMatrixGetOneSchemeInd,      /***************<< ��ȡ���󷽰�һ������ָʾ  >>****************	
                                             *[��Ϣ��]			 
                                             *    ITInnerMatrixScheme
                                             */  
                                                
    h_ctrl_innerMatrixSaveSchemeCmd,        /***********************<< ���淽��  >>************************	
                                             *[��Ϣ��]			 
                                             *    +  ITInnerMatrixScheme
                                             */ 
                                                
    h_ctrl_innerMatrixSaveSchemeInd,        /*********************<< ���淽��ָʾ  >>**********************	
                                             *[��Ϣ��]			 
                                             *    +  ITInnerMatrixScheme
                                             */ 
                                                
    h_ctrl_innerMatrixSetCurSchemeCmd,      /*****************<< ����ָ������Ϊ��ǰ����  >>****************	
                                             *[��Ϣ��]			 
                                             *	  +  u8  ��������
                                             */ 
                                                
    h_ctrl_innerMatrixSetCurSchemeInd,      /**************<< ����ָ������Ϊ��ǰ����ָʾ >>****************	
                                             *[��Ϣ��]			 
                                             *	  +  u8  ��������
                                             */ 
                                                
    h_ctrl_innerMatrixCurSchemeCmd,         /********************<< ��ȡ��ǰ��������  >>*******************	
                                             *[��Ϣ��]			 
                                             *  ��  
                                             */                                                 
                                                
    h_ctrl_innerMatrixCurSchemeInd,         /*****************<< ��ȡ��ǰ��������ָʾ  >>******************	
                                             *[��Ϣ��]			 
                                             *    +  u8  ��������
                                             */
    //��չ��ƵԴ
  
	h_ctrl_getVideoSourceInfoCmd,           /*******************<< ��ȡ�ն���ƵԴ��Ϣ  >>******************	
                                             *[��Ϣ��]			 
                                             *    NULL
                                             */   

    h_ctrl_allVideoSourceInfoInd,           /******************<< �ն�ȫ����ƵԴָʾ  >>*******************	
                                             *[��Ϣ��]			 
                                             *    +  tagITVideoSourceInfo[]
                                             */   
												 
    h_ctrl_setVideoSourceInfoCmd,           /*******************<< �����ն���ƵԴ��Ϣ  >>******************	
                                             *[��Ϣ��]			 
                                             *    +  tagITVideoSourceInfo
                                             */   

    h_ctrl_VideoSourceInfoInd,              /******************<< �ն���ƵԴ��Ϣָʾ  >>*******************	
                                             *[��Ϣ��]			 
                                             *    +  tagITVideoSourceInfo
                                             */
			
    h_ctrl_selectExVideoSourceCmd,          /********************<< ��չ��ƵԴѡ��  >>*********************	
                                             *[��Ϣ��]			 
                                             *    +  u8     EX_VIDEOSOURCE_BASE ��ַ 
                                             *              ��EX_VIDEOSOURCE_BASE������չ��ƵԴ��1�Ŷ˿�
                                             */
	
    h_ctrl_ViewBroadcastingSrcCmd,          /*��ϯ�ն�ǿ�ƹ㲥, ��Ϣ��: u8 (opr_start-��ʼ��opr_stop��ȡ��)*/
    
    h_ctrl_SatDConfAddrInd,                 /*******************<< ���Ƿ�ɢ������յ�ַ֪ͨ >>*************
                                             * Mcu-->ter
                                             *[��Ϣ��](��������)
                                             *    +   u32   ��һ·��Ƶ��ַ
                                             *    +   u16   ��һ·��Ƶ�˿�
                                             *    +   u32   ��һ·��Ƶ��ַ
                                             *    +   u16   ��һ·��Ƶ�˿�
                                             *    +   u32   �ڶ�·��Ƶ��ַ
                                             *    +   u16   �ڶ�·��Ƶ�˿�
                                             */

	 h_ctrl_videoFormatChangeCmd,            /*********************<< ��Ƶ�ֱ��ʵ���  >>********************
											 * Mcu-->ter
											 *[��Ϣ��]
											 *
											 *    +   u8  ͨ������   LOGCHL_VIDEO      (Ĭ������Ƶͨ��)
											 *    +   u8  �ֱ������� VIDEO_FORMAT_CIF, VIDEO_FORMAT_QCIF, VIDEO_FORMAT_SQCIF_* ��
											 */

    

    h_ctrl_setAudioVolumeCmd,               /*********************<<  �ն���������   >>********************
                                             * Mcu-->ter
                                             *[��Ϣ��]
                                             *
                                             *    +   u8  ��������(NOTE: VOLUME_TYPE_OUT or VOLUME_TYPE_IN)
                                             *    +   u8  �����������(NOTE: vx linux 0��32; PCMT: 0��255)
                                             */
    
    h_ctrl_someOfferingNtf,                 /********************<<  �ն�֪ͨͨ����Ϣ >>*******************
                                             * Mcu-->ter
                                             *[��Ϣ��]
                                             *
                                             *    Mcu2MtNtfMsgBodyType
                                             */ 
                                             
    h_ctrl_videoFrameRateChangeCmd,         /********************<<  (��һ·)��Ƶ����֡�ʵ��� >>***********
                                             * Mc-->ter
                                             *[��Ϣ��]
                                             *
                                             *    +   u8  ����֡��
                                             */

	h_ctrl_removeMixMemberCmd,				/********************<<  �Ƴ����ƻ����е��ն� (����ϯ������Ч) >>*******************
											 * Mt-->Mc
											 *[��Ϣ��]
											 *
											 *    +   TMt ����
											 * 
                                             */
	h_ctrl_discussParamInd,					/*******************<< ������Ϣ֪ͨ>>***************************
											 * Mt-->Mc
											 * [��Ϣ��]
											 * + TDiscussParam
											 *
											 */
	h_ctrl_videoFormatRecoverCmd,			/******************<<  �ն˷ֱ��ʻָ�����   >>****not in use now**********
											 * ter-->Mt
											 * [��Ϣ��]  ��
											 */
	h_ctrl_mtSelectVmpReq,					/*******************<< �նˣ�������ϯMT��ѡ������ϳ����� >>**************
											 * ter --> MC
											 * [��Ϣ��] u8	1��start,0��stop
											 */
	h_ctrl_mtSelectVmpRsp,					/*******************<< �նˣ�������ϯMT��ѡ������ϳ�Ӧ�� >>**************
											 * MC --> ter
											 * [��Ϣ��] u8  ok/fail(1��ok��0��fail)
											 */	
    h_ctrl_mtSpeakStatusNtf,                /*******************<< �ն� ���뷢���е��ն�              >>**************
											 * MC --> ter
											 * [��Ϣ��] emSpeakerStatus
                                             *
                                                             emWaiting       = 1,        //�ȴ�ͬ�⣻mcu���ᷢ�ʹ�״̬���ն��ڷ������� �� ��Ϊ������֪ͨ �� ֮ǰ���Զ������״̬
                                                             emAgreed        = 2,        //�����ˣ�
                                                             emDenid         = 3,        //���뱻�ܾ���
                                                             enCanceled      = 4,        //��ȡ�����ԣ�
                                             */	

    h_ctrl_confSpeakModeNtf,                 /*******************<< �ն� ��������ն�                 >>**************
											 * MC --> ter
											 * [��Ϣ��] emConfSpeakMode
                                                            emNormal            = 0,        //��ͨ����ģʽ����ϯָ��/���ָ��/һ����ն�����
                                                            emAnswerInstantly   = 1         //����ģʽ
                                             */	

    h_ctrl_applycancelspeakerReq,               /*******************<< �������ն� ��> MCU                 >>**************
											 * ter --> MC
											 * [��Ϣ��] u8:0-ȡ������ 1-���뷢��
                                             */	

    h_ctrl_applycancelspeakerRsp,               /*******************<< MCU ��>  �������ն�                >>**************
											 * MC --> ter
											 * [��Ϣ��] u8:0-ȡ������ 1-���뷢��
														u8 result: granted/denied
                                             */	

	h_ctrl_videoFpsChangeCmd,               /*********************<< ��Ƶ֡�ʵ���  >>********************
											 * Mcu-->ter
											 *[��Ϣ��]
										 	 *
										 	 *    +   u8  ͨ������   LOGCHL_VIDEO      (Ĭ������Ƶͨ��)
											 *    +   u8  ֡��ֵ 
											 */
	h_ctrl_videoAliasCmd,               /*********************<< mcu��ȡ�ն���ƵԴ����  >>********************
										 * Mcu-->ter
										 *[��Ϣ��] ��
										 *
										 *    
										 *    
										 */
	h_ctrl_videoAliasInd,               /*********************<< �ն���ƵԴ����ָʾ  >>********************
										* ter-->Mcu
										*[��Ϣ��]
										*  u8 byVidNum����ƵԴ������+ u8 byVidIdx����ƵԴ�˿�������+   
										*   u8 byAliaseLen���������ȣ�+ s8 *pchAlias��������+ 
										*  u8 byVidIdx����ƵԴ�˿�������+ u8 byAliaseLen���������ȣ�+  
										*   s8 *pchAlias��������+ ...
										*    
										*    
										*/
	h_ctrl_ChgSecVidSendCmd	= 101 + 134,/*********************<< �����ն�˫���������� >>********************
										 * Mcu-->ter
										 *[��Ϣ��] 
										 *u8 0��ֹͣ˫��  1������˫��
										 *    
										 *    
										 */
//[20120613]
	h_ctrl_transparentMsgNtf,           /*********************<< ���桢�ն�͸����Ϣ  >>********************
										* ter<-->Mcu
										*[��Ϣ��]
										*     ������Ϣ���Ͳ�ͬ����Ϣ�����ݲ�ͬ
										*      
										*/  
										
	h_ctrl_CodingFormNtf,                /*********************<< ��h245������������Զ˷��͸÷Ǳ���Ϣͨ��Զ˱��˵ı��뷽ʽ  >>********************
										 * ter<-->Mcu
										 *[��Ϣ��]
									     * u8(���뷽ʽ)
										 *      
										 */
    h_ctrl_nonstandardVrsDef,           /***************<<�Ǳ��Զ��塷******************
                                         * ter<-->Mcu
                                         *[��Ϣ��]
                                         *     ������Ϣ���Ͳ�ͬ����Ϣ�����ݲ�ͬ
                                         *     �ϲ�����ҵ��Э����Ϣ�������ͺ���Ϣ����
                                         *
						                 */
//[20140704]
	h_ctrl_StartMtVmpReq,		/********** <<�ն˿�������ϳ�����>>*************************
   								 * ter -->Mcu
   								 * [��Ϣ��]
								 * u8(����ϳ����ͣ�vccommon.h�ж���) ) 
								 * u8(����ϳɷ�ʽ��vccommon.h�ж���) ) 
  	 							 * u8(����ϳɷ��vccommon.h�ж���) 
   								 * u8(byLen-��Ч��Ա��)
   								 * ��u8(ͨ����)  + TVMPMember��* byLen
								 */

	h_ctrl_StartMtVmpRsp,		/***********<<ֹͣ�ն˻���ϳ�����>>**************************          
								 * ter --> Mcu  
								 * [��Ϣ��]
								 * u8(����ϳ����ͣ�vccommon.h�ж���)
								 */

	h_ctrl_StartMtVmpNotify,		/************<<�ն˿�������ϳ�ͨ��>>***************************
   									 * Mcu -->ter
   									 * [��Ϣ��]
   									 * u8(0-�ɹ� 1-ʧ��)
									 * u8(����ϳ����ͣ�vccommon.h�ж���)
								 	 *  ���³ɹ�ʱ���� *
									 * u8(����ϳɷ�ʽ��vccommon.h�ж���)
   									 * u8(����ϳɷ��vccommon.h�ж���) 
   									 * u8(byLen-��Ч��Ա��)
   									 * (u8(ͨ����) + TVMPMember) * byLen
									 */


	h_ctrl_StopMtVmpReq, 		/************<<ֹͣ�ն˻���ϳ�����>>***************************          
								 * ter --> Mcu  
								 * [��Ϣ��]
								 * u8(����ϳ����ͣ�vccommon.h�ж���)
								 */

	h_ctrl_StopMtVmpRsp,		/************<<ֹͣ�ն˻���ϳ�����Ӧ��>>***************************          
								 * Mcu --> ter 
								 * [��Ϣ��]
								 * u8(0-�ɹ� 1-ʧ��)
								 * u8(����ϳ����ͣ�vccommon.h�ж���) */

	h_ctrl_StopMtVmpNotify,   		/************<<ֹͣ�ն˻���ϳ�����Ӧ��>>***************************          
									 * Mcu --> ter 
									 * [��Ϣ��]
									 * u8(0-�ɹ� 1-ʧ��)
									 * u8(����ϳ����ͣ�vccommon.h�ж���) 
									 */


	h_ctrl_ChangeMtVmpReq,		/************<<�����ն˻���ϳ�����>>***************************
 								 * ter -->Mcu
 								 * [��Ϣ��]
								 * u8(����ϳ����ͣ�vccommon.h�ж���)
								 * u8(����ϳɷ�ʽ��vccommon.h�ж���)
 								 * u8(����ϳɷ��vccommon.h�ж���) 
 								 * u8(byLen-��Ч��Ա��)
 								 * ��u8(ͨ����)  + TVMPMember��* byLen
								 */

	h_ctrl_ChangeMtVmpRsp, 		/************<<�����ն���������ϳ�����Ӧ��>>***************************
 								 * Mcu -->ter
 								 * [��Ϣ��]
								 * u8(0-�ɹ� 1-ʧ��)
								 * u8(����ϳ����ͣ�vccommon.h�ж���)
								 */

	h_ctrl_ChangeMtVmpNotify,		/************<<�����ն˻���ϳ�ͨ��>>***************************
 									 * Mcu -->ter
 									 * [��Ϣ��]
									 * u8(0-�ɹ� 1-ʧ��)
									 * u8(����ϳ����ͣ�vccommon.h�ж���)
									 *  ���³ɹ�ʱ���� *
									 * u8(����ϳɷ�ʽ��vccommon.h�ж���)
 									 * u8(����ϳɷ��vccommon.h�ж���) 
 									 * u8(byLen-��Ч��Ա��)
 									 * (u8(ͨ����)  + TVMPMember) * byLen
									 */
//--20140704--

	h_ctrl_mcuvccommonnonstandend   = 299,


	//�Զ�����Ϣ��ʼ
	h_ctrl_nonstandstart			= 300,	//
	
	h_ctrl_quietRequest				= 301,  //Զ�˾�������,				[outgoing]: [TTERLABEL]
	h_ctrl_quietResponse			= 302,  //Զ�˾�����Ӧ				[incoming]: [TTERLABEL+u8:CtrlResult]

	h_ctrl_cancelQuietRequest		= 303,  //ȡ��Զ�˾�������			[outgoing]: [TTERLABEL]
	h_ctrl_cancelQuietResponse		= 304,  //ȡ��Զ�˾�����Ӧ			[incoming]: [TTERLABEL+u8:CtrlResult]

	h_ctrl_muteRequest				= 305,  //Զ�˱�������,				[outgoing]: [TTERLABEL]
	h_ctrl_muteResponse 			= 306,  //Զ�˱�����Ӧ				[incoming]: [TTERLABEL+u8:CtrlResult]

	h_ctrl_cancelMuteRequest		= 307,  //ȡ��Զ�˱�������			[outgoing]: [TTERLABEL]
	h_ctrl_cancelMuteResponse		= 308,  //ȡ��Զ�˱�����Ӧ			[incoming]: [TTERLABEL+u8:CtrlResult]

	h_ctrl_setVACReqequest			= 309,  //���������л�(��������)	[outgoing]: [u8+DW] 0�����������л�1��ȡ�������л�+1 DW ��������(0~100֮���һ��ֵ),����û���������ޣ���ʱʹ��ȱʡ����������
	h_ctrl_setVACResponse			= 310,  //���������л����			[incoming]: [u8:CtrlResult](�����Ƕ����ò����Ľ�������Ǳ�����ǰ�����л���״̬�����磬ȡ�������л��Ľ��Ϊ�ɹ�����ʾȡ�������л������óɹ���)

	h_ctrl_startDiscussRequest		= 311,  //��ʼ��������				[outgoing]: NULL
	h_ctrl_startDiscussResponse		= 312,  //�������۽��				[incoming]: [u8:CtrlResult]�ն��յ��������,���л᳡����,ȫ��ȡ������
	
	h_ctrl_setMultiPicRequest		= 313,  //���ö໭��				[outgoing]: TMultiPic
	h_ctrl_setMultiPicResponse		= 314,  //

	h_ctrl_notInConfTerminalListRequest = 315,//��������δ���᳡��	[outgoing]: NULL
	h_ctrl_notInConfTerminalListResponse= 316,//����δ���᳡��Ӧ��	[incoming]: [TTERINFO[]]

	h_ctrl_callTerminal				= 317,  //�������߻᳡				[outgoing]: [TTERLABEL]
	h_ctrl_disconnectTerminal		= 318,  //�Ҷ��ն�					[outgoing]: [TTERLABEL]

	h_ctrl_selectSpeakingUserRequest= 319,	//��������					[outgoing]: [TTERLABEL]
	h_ctrl_selectSpeakingUserResponse=320,  //�������Խ��				[incoming]: [TTERLABEL+u8:CtrlResult]
	
	h_ctrl_setPicSwitch				 =321,	//��,�໭���л�				[outgoing]: [u8] 0:������;1:�໭��
    
    h_ctrl_capabilitiesInd           =322,  //��ͨ����ָʾ              [incoming]: [TCAPINFO]

    h_ctrl_serialPortData            =323,  //��������                  [incoming]&[outgoing]: [TCOMDATA]


	h_ctrl_setChanMultiCastAddr		 =400,  //����ͨ���鲥��ַ			[incoming]&[outgoing]: [TCHANMULTICAST]

	h_ctrl_serialNumber      		 =401,  //���к�    				[incoming]&[outgoing]: [u8[]] 
    h_ctrl_startDataConfRequest      =402,  //����ʼ���ݻ���          NULL

    h_ctrl_startDataConfResponse     =403,  //Ӧ��ʼ���ݻ���          [incoming]&[outgoing]: u8: result
	h_ctrl_askVcsOccupyPermit	     =500,	//
	
	h_ctrl_askVcsOccupyPermitResp    =501,  //

	h_ctrl_VersionIdInd              =600, // ��Ϣ��Ϊu8[LEN_256]
	
	h_ctrl_KdvpExtraConfNSNInfo      =601, // ����192���ն��б�������Ǳ� [incoming]&[outgoing]

    h_ctrl_end
};

//�Ǳ��������
enum NonstandardType 
{
    emNonstandardTypeInvalidType = 0,
    emNonstandardTypeRequest,
    emNonstandardTypeResponse,
    emNonstandardTypeCommand,
    emNonstandardTypeIndication
};

//add by yj for QUERY [20121212]
//��ǰƽ̨��֧�ֵ��б��ѯ����
enum emPlatformCap
{
	KdvPlatformCapStart	= 0,
	KdvPlatformCapTerLIst,					//�����ն��б�
	KdvPlatformCapConfList,					//�����б�
	KdvPlatformCapCreateConfwithTerlist,	//�ټ���������
	KdvPlatformCapJoinCofByConfList,		//�μӻ�������
	KdvPlatformCapGlobalAddrBook,			//ȫ�ֵ�ַ��
	KdvPlatformCapVideoRecordBroadcast,		//¼������
	KdvPlatformCapEnd,
};

typedef struct tagPlatformCap
{
	u32 m_dwCap;
	
	void Clear(){  m_dwCap = 0; } 

	BOOL SetAllCap( u32 dwCap )
	{
		if ( dwCap <= (0x01<< KdvPlatformCapStart)  || dwCap >= (0x01<< KdvPlatformCapEnd) )
			return FALSE;
		m_dwCap = htonl(dwCap);
		return TRUE;
	}
	
	u32 GetAllCap()
	{
		return ntohl( m_dwCap );
	}

	BOOL AddCap( emPlatformCap emCap )
	{	
		if ( emCap <= KdvPlatformCapStart  || emCap >= KdvPlatformCapEnd )
			return FALSE;
		m_dwCap = ntohl(m_dwCap);
		m_dwCap = ( m_dwCap | (0x01<< emCap ) );
		m_dwCap = htonl(m_dwCap);
		return TRUE;
	}

	BOOL RemoveCap( emPlatformCap emCap )
	{
		if ( emCap <= KdvPlatformCapStart  || emCap >= KdvPlatformCapEnd )
			return FALSE;
		m_dwCap = ntohl(m_dwCap);
		m_dwCap = ( m_dwCap & ~(0x01<< emCap ) );
		m_dwCap = htonl(m_dwCap);
		
		return TRUE;
	}

	BOOL IsSupport(emPlatformCap emCap )
	{
		if ( emCap <= KdvPlatformCapStart  || emCap >= KdvPlatformCapEnd )
			return FALSE;
		m_dwCap = ntohl(m_dwCap);
        if (((s32)m_dwCap & (0x01<<emCap)) ==  (0x01<<emCap))
		{
			m_dwCap = htonl(m_dwCap);
			return TRUE;
		}
		else
		{
			m_dwCap = htonl(m_dwCap);
			return FALSE;
		}
	}
}TPlatformCap;
//end [20121212]

///////////////////////////////// ����ֵ���� ///////////////////////////////

//API����ִ�н��
enum ActResult 
{
    act_err = -1,
	act_ok
};

//add by yj for callmake error return [20120618]
enum CallMAkeErrReason 
{
    err_unknow				= -1,	//δ֪ԭ��
	err_full_call			= -2,	//��������
	err_set_param			= -3,	//��������ò�������(������ַ)
	err_null_ptr			= -4,	//ָ��ΪNULL��ָ���buffer��С��ƥ��	
	err_set_address			= -5,	//����ʱЭ��ջ�ڲ��жϵ�ַ��������	
	err_already_setup		= -6,	//�Ѿ����й�	
	err_autoRas_PrepareARQ	= -7,	//����ARQʧ��
	err_autoRas_Register	= -8,   //ע��ʧ��
	err_Q931_Connect		= -9,	//Q931����ʧ��
	err_iptype_notmatch		= -10,	//����Դ��ַ��Ŀ�ĵ�ַ���Ͳ�һ��(����IP��)
};
//end [20120618]

enum callBackResult 
{
    cb_err = -1,
    cb_ok
};
///////////////////////////////// �������� ///////////////////////////////

// IP��ַ����
enum TransportAddrType 
{
	addr_uca,		//unicast
	addr_mca,		//multicast
    addr_err = 0xff
};

// ���е�ַ����
enum CallAddrType
{
    cat_err = -1,
	cat_ip  = 1, 	//IP����
	cat_alias	   	//��������
};

#ifndef CM_H
typedef enum
{
	cmCreate,
	cmJoin,
	cmInvite,
	cmCapabilityNegotiation,
	cmCallIndependentSupplementaryService,
	cmLastCG
}cmConferenceGoalType;

typedef enum
{
    cmCallTypeP2P,
	cmCallTypeOne2N,
	cmCallTypeN2One,
	cmCallTypeN2Nw
}cmCallType;

typedef enum
{
    cmEndpointTypeTerminal,
	cmEndpointTypeGateway,
	cmEndpointTypeMCU,
	cmEndpointTypeGK,
	cmEndpointTypeUndefined,
	cmEndpointTypeSET
}cmEndpointType;

typedef enum
{
    cmRASDisengageReasonForcedDrop,
	cmRASDisengageReasonNormalDrop,
	cmRASDisengageReasonUndefinedReason
}cmRASDisengageReason;

typedef enum
{
    cmRASUnregReasonReregistrationRequired,
	cmRASUnregReasonTtlExpired,
	cmRASUnregReasonSecurityDenial,
	cmRASUnregReasonUndefinedReason,
	cmRASUnregReasonMaintenance
}cmRASUnregReason;

typedef enum
{
    cmRASReasonResourceUnavailable,             /* GRJ, RRJ, ARJ, LRJ - gatekeeper resources exhausted */
    cmRASReasonInsufficientResources,           /* BRJ */
    cmRASReasonInvalidRevision,                 /* GRJ, RRJ, BRJ */
    cmRASReasonInvalidCallSignalAddress,        /* RRJ */
    cmRASReasonInvalidRASAddress,               /* RRJ - supplied address is invalid */
    cmRASReasonInvalidTerminalType,             /* RRJ */
    cmRASReasonInvalidPermission,               /* ARJ - permission has expired */
                                                /* BRJ - true permission violation */
 //7                                            /* LRJ - exclusion by administrator or feature */
    cmRASReasonInvalidConferenceID,             /* BRJ - possible revision */
    cmRASReasonInvalidEndpointID,               /* ARJ */
    cmRASReasonCallerNotRegistered,             /* ARJ */
    cmRASReasonCalledPartyNotRegistered,        /* ARJ - can't translate address */
    cmRASReasonDiscoveryRequired,               /* RRJ - registration permission has aged */
    cmRASReasonDuplicateAlias,                  /* RRJ - alias registered to another endpoint */
    cmRASReasonTransportNotSupported,           /* RRJ - one or more of the transports */
    cmRASReasonCallInProgress,                  /* URJ */
    cmRASReasonRouteCallToGatekeeper,           /* ARJ */
    cmRASReasonRequestToDropOther,              /* DRJ - can't request drop for others */
    cmRASReasonNotRegistered,                   /* DRJ, LRJ, INAK - not registered with gatekeeper */
    cmRASReasonUndefined,                       /* GRJ, RRJ, URJ, ARJ, BRJ, LRJ, INAK */
    cmRASReasonTerminalExcluded,                /* GRJ - permission failure, not a resource failure */
    cmRASReasonNotBound,                        /* BRJ - discovery permission has aged */
    cmRASReasonNotCurrentlyRegistered,          /* URJ */
    cmRASReasonRequestDenied,                   /* ARJ - no bandwidrg available */
//23                                                /* LRJ - cannot find location */
    cmRASReasonLocationNotFound,                /* LRJ - cannot find location */
    cmRASReasonSecurityDenial,                  /* GRJ, RRJ, URJ, ARJ, BRJ, LRJ, DRJ, INAK */
    cmRASReasonTransportQOSNotSupported,        /* RRJ */
    cmRASResourceUnavailable,                   /* Same as cmRASReasonResourceUnavailable */
    cmRASReasonInvalidAlias,                    /* RRJ - alias not consistent with gatekeeper rules */
    cmRASReasonPermissionDenied,                /* URJ - requesting user not allowed to unregister specified user */
    cmRASReasonQOSControlNotSupported,          /* ARJ */
    cmRASReasonIncompleteAddress,               /* ARJ, LRJ */
    cmRASReasonFullRegistrationRequired,        /* RRJ - registration permission has expired */
    cmRASReasonRouteCallToSCN,                  /* ARJ, LRJ */
    cmRASReasonAliasesInconsistent,             /* ARJ, LRJ - multiple aliases in request identify distinct people */
    cmRASReasonAdditiveRegistrationNotSupported,/* RRJ */
    cmRASReasonInvalidTerminalAliases,          /* RRJ */
    cmRASReasonExceedsCallCapacity,             /* ARJ - destination does not have the capacity for this call */
    cmRASReasonCollectDestination,              /* ARJ */
    cmRASReasonCollectPIN,                      /* ARJ */
    cmRASReasonGenericData,                     /* GRJ, RRJ, ARJ, LRJ */
    cmRASReasonNeededFeatureNotSupported,       /* GRJ, RRJ, ARJ, LRJ */
    cmRASReasonUnknownMessageResponse,          /* XRS message was received for the request */
    cmRASReasonHopCountExceeded                 /* LRJ */
}cmRASReason;

typedef struct
{
    int timestamp;      /* -1 if optional; */
    int expirationTime; /* -1 if optional;*/
    int logicalChannelNumber;
}cmUserInputSignalRtpStruct;

typedef struct
{
    char signalType;
    int duration;
    cmUserInputSignalRtpStruct cmUserInputSignalRtp;/* if logicalchannel == 0 -optional*/
}cmUserInputSignalStruct;
#endif//CM_Hû�а���cm.h

#ifndef CMCTRL_H
typedef enum 
{
    cmCapReceive=1,
    cmCapTransmit=2,
    cmCapReceiveAndTransmit=3
} cmCapDirection;
#endif//CMCTRL_H û�а���cm.h

//���жϿ�ԭ��
enum CallDisconnectReason 
{
	reason_busy = 1,
	reason_normal,
	reason_rejected,
	reason_unreachable,
	reason_local,
	reason_unknown,

	reason_nobandwidth,                  //ARQ�ܾ���û�д���
	reason_nopermission,                 //�������ؾܾ�
	reason_unreachablegatekeeper,         //���ز��ɴ�for arq
	reason_mcuoccupy,
	reason_reconnect,
	reason_confholding,
	reason_hascascaded                 
};

//Facility Reason
enum FacilityReason 
{
	routeToGK,				
	callForward,				
	routeToMC,
	confListChoice,
	startH245,
	unknown
};

//���Ӿ������
enum MasterSlaveResult 
{
	msdse_master,		//����Ϊmaster
	msdse_slave,		//����Ϊslave
    msdse_err = 0xff    
};

//�����������
enum CapExchangeResult 
{
	cese_accept,		//�Զ˽��ܱ�������
	cese_reject,		//�Զ˾ܾ���������
    cese_err = 0xff
};

//�������:makeTerminalBroadcaster��sendThisSource�Ĳ�����ʽ
enum CtrlMode 
{
	mode_invalid = -1,
	mode_command,
	mode_request
};

//�������:����-Ӧ��ʽ���ؽ��
enum CtrlResult 
{
	ctrl_err = -1,
	ctrl_granted,		//�ɹ�
	ctrl_denied			//�ܾ�
};

//��������
enum AliasType
{
	type_aliastype,
	type_e164 = 0x1,
	type_h323ID,
	type_email,
	type_epID,
	type_GKID,
	type_partyNumber,
	type_others
};

//��������
enum  DataType 
{
	type_none = 0,
	type_audio,
	type_video,
	type_data,
};

#ifndef MCUCASC_ADAPTER_COMMON
#define MCUCASC_ADAPTER_COMMON

//ý������
//guzh [12/14/2007] ������Χȷ��
//guzh [03/27/2008] ������ʷԭ��a_typeEnd��v_typeEnd�ȷ�Χ��׼ȷ������������ʹ��
//��ֱ��ʹ�� IsAudioType, IsAudioType, IsDataType�Ƚӿ�
enum  PayloadType 
{
    emPayloadTypeBegin = 0,
        //��Ƶ��ʽ
        a_typeBegin,
        a_g711a,
        a_g711u,
        a_g722,
        a_g7231,
        a_g728,
        a_g729,
        a_mp3,
        
        a_g723,
        a_g7221,//����a_g7221c
        
        // guzh
        a_mpegaaclc = 11,
        a_mpegaacld = 12,
		a_g719,//ruiyigen 20091012
        
        // �������ϰ汾����
        v_mpeg4 = 17,    
        v_h262 = 18,
        
        a_typeGeneric = 48,   // �ڲ�ʹ��
        
        a_typeEnd = 49,
        
        //��Ƶ��ʽ
        v_typeBegin = 50,	
        v_h261,
        v_h263,
        v_h263plus,
        v_h264,
        //v_mpeg4,
        //v_h262,
        v_generic = 97,
        v_extended = 98,
        v_typeEnd = 99,
        
        //���ݸ�ʽ
        d_typeBegin = 100,	
        d_t120,
        d_h224,
        d_typeEnd = 149,
        
        t_h235 = 150, //�ڲ�ʹ��
        t_mmcu,       //����ͨ��
        t_none,       //��ͨ����֧��, �����ڼ���
        t_nonStandard,
        t_huawei,

		//add for huawei nostandrd [20130427]
		t_huawei_5,
		t_huawei_6,
		t_huawei_7,
		//end [20130427]

		//add for ZTE nostandrd [20130507]
		t_ZTE_8,	//audio
		t_ZTE_10,	//audio
		t_ZTE_11,	//audio
		t_ZTE_13,	//video ��δ����ͬʱ������
		t_ZTE_21,	//video
        //end [[20130507]
    emPayloadTypeEnd = 255
};

#define PayloardIsAudioType( paylord )  \
( (a_typeBegin < paylord && paylord < a_typeEnd && paylord != v_mpeg4 && paylord != v_h262) )

#define PayloardIsVideoType( paylord )  \
( ( (v_typeBegin < paylord && paylord < v_typeEnd) || paylord == v_mpeg4 || paylord == v_h262) )

#define PayloardIsDataType( paylord )  \
( (d_typeBegin < paylord && paylord < d_typeEnd) )



//�ֱ���
typedef enum
{
	emResolutionBegin,
	    emSQCIF,
	    emQCIF,
	    emCIF,
	    emCIF2,
	    emCIF4,    // 576SD: stands for D1: 720*576
	    emCIF16,
		    
	    em352240,
	    em704480,  // 480SD

	    em640480,
	    em800600,
	    em1024768,

	    emAUTO,
    emResolutionEnd
}emResolution;

// High Definition Resolutions(1080i is i-mode, others are p-mode)
typedef enum
{    
    emW4CIF = 14,   // Wide4CIF 16:9 1024*576
    emHD720,        // 720   1280*720
    emSXGA,         // SXGA  1280*1024
    emUXGA,         // UXGA  1600*1200
    emHD1080,       // 1080  1920*1080	
	
	em1280x800,
	em1280x768,
	em1366x768,
}emResolutionHD;
#endif

//������صĲ���
enum CallParamType
{
	cpt_ConferenceGoalType,					//�����Ŀ������ cmConferenceGoalType
	cpt_CallType,							//��������       cmCallType
	cpt_callId,								//����ID		 char[16]
	cpt_callCrv,							//����CRV		 int
	cpt_confId								//����ID		 char[16]
};

//�ն�����
typedef enum
{
	emEndpointTypeUnknown = 0,
	emEndpointTypeMT	  = 0x01,
	emEndpointTypeMCU	  = 0x02,
	emEndpointTypeGK      = 0x04
}emEndpointType;

//�ն�����ֵ
typedef enum
{
	emMsMT			= 50,
	emMsMT_MC		= 70,
	emMsMCU			= 190,
	emMsActiveMC	= 240,
}emMsTerminalType;

//�豸���̱�ʶ��Ϣ
enum VendorProductId
{
	vendor_MICROSOFT_NETMEETING = 1,
	vendor_KEDA,
	vendor_HUAWEI,
	vendor_POLYCOM,
    vendor_POLYCOM_MCU,
	vendor_TANDBERG,
	vendor_RADVISION,
	vendor_VCON,
	vendor_SONY,
	vendor_VTEL,
	vendor_ZTE,
	vendor_ZTE_MCU,
    vendor_CODIAN,
	vendor_AETHRA,
	//[20120613]
	vendor_CHAORAN,
	//end
	vendor_UNKNOWN,
	vendor_END
};

/*�غ����͵��ڲ�ת��:
|<--------------���ܺ�H239���غ�ת��---------- >|<���ֽ�Ϊ�ϲ�ʹ�õ�����>|
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+  0  +  0  +  0  + 0  +  1  +  1  +  1  +  1  +  payloadType           +             
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                       + H239+ AES + DES +NoEnc+   
*/
//��������
typedef enum
{
    emEncryptTypeNone = 1,//00000001
    emEncryptTypeDES  = 2,//00000010
    emEncryptTypeAES  = 4,//00000100

    emEncryptTypeH239 = 8,//00001000

}emEncryptType;

//H323 Annex Q
/*   
 *   h.281 encoded in host bit order:
 *   +-------+---------+--------+---------+--------+---------+--------+---------+
 *   +   P   | R=1/L=0 |    T   | U=1/D=0 |    Z   | I=1/O=0 |    F   | I=1/O=0 |
 *   +-------+---------+--------+---------+--------+---------+--------+---------+
 */
enum feccAction
{
	actionInvalid				= 0,  
	actionStart					= 0x01,  //��ʼ
	actionContinue				= 0x02,  //����
	actionStop					= 0x03,  //ֹͣ
	actionSelectVideoSource		= 0x04,  //ѡ����ƵԴ
	actionVideoSourceSwitched	= 0x05,  //�л���ƵԴ
	actionStoreAsPreset			= 0x06,  //�洢Ԥ��λ
	actionActivatePreset		= 0x07,  //�ָ���Ԥ��λ
	actionAutoFocus				= 0x11,  //�Զ�����
};

//PTFZ codes, parameters for action Start, continue and stop.
enum feccPTFZRequest
{
	requestInvalid				= 0,
	requestPanLeft				= 0x80,	//�����ƶ�
	requestPanRight				= 0xc0,	//�����ƶ�
	requestTiltUp				= 0x30,	//�����ƶ�
	requestTiltDown				= 0x20,	//�����ƶ�
	requestFocusIn				= 0x03,	//����
	requestFocusOut				= 0x02,	//Զ��
	
	requestZoomIn				= 0x0c,	//��Ұ��С
	requestZoomOut				= 0x08,	//��Ұ���

	requestBrightnessUp			= 0x01,	//���ȼ�(nonstandard)
	requestBrightnessDown		= 0x04  //���ȼ�(nonstandard)
};

typedef enum
{
	annexQNotInited				= -20,
	annexQBindError				= -15,
	annexQParamError			= -14,
	annexQLockError				= -12,	
	annexQCodingError			= -10,
	annexQSendError				= -9,	
	annexQGeneralError			= -5,
	annexQOk					= 1
}annexQResult;

//for tanderg
enum feccVideoSourceNumber
{
    VideoSourceDefault               = 0,    //��ǰ��ƵԴ
    VideoSourceMainCamera            = 1,    //����ƵԴ
    VideoSourceAuxCamera             = 2,    //������ƵԴ
    VideoSourceDocCamera             = 3,    //�ļ�չʾ̨
    VideoSourceAuxDocCamera          = 4,    //�����ļ�չʾ̨������̩��Ϊvcr
    VideoSourceVideoPlaybackSource   = 5,    //vcr������̩��ΪPC
};

//H239
typedef enum
{
    emH239InfoTypeInvalid		        = 0,

    emH239FlowControlReleaseRequest     = 1,
    emH239FlowControlReleaseResponse    = 2,
    emH239PresentationTokenRequest      = 3,
    emH239PresentationTokenResponse     = 4,
    emH239PresentationTokenRelease      = 5,
    emH239PresentationTokenIndicateOwner= 6,

    emH239InfoTypeEnd
}emH239InfoType;

typedef enum
{
	emStyle2p  = 0x07,
	emStyle3p  = 0x08,
	emStyle4p  = 0x00,
	emStyle6p  = 0x02,
	emStyle8p  = 0x04,
	emStyle9p  = 0x01,
	emStyle13p = 0x06,
	emStyle13  = 0x05,
	emStyle16p = 0x03,
	emStyleEnd
}emPicStyle;

typedef enum
{
	emChanUnkown = 0,
	emChanVideo1 = 1,
	emChanAudio	 = 2,
	emChanVideo2 = 3
}emChanID;

typedef enum
{
    emComUnkown  = 0,
    emComRS232   = 1,
    emComRS422   = 2,
    emComRS485   = 3,
    emComEnd
    
}emComType;

// guzh [9/25/2007] ǰ���������
typedef enum
{
    emFECNone   = 0x00,
    emFECRaid5  = 0x01,
    emFECRaid6  = 0x02,
	emFECNonStd    = 0x04 //��˾�Լ���NsmFec add by shigubin 20130228
}emFECType;

typedef enum
{
    emNALNode            =  0x00,       // invalid
    emNALSignal          =  0x01,       // single
	emNALNoneInterleaved =  0x02,       // not interleaved
	emNALInterleaved     =  0x04        // interleaved
}emH264NALMode;


typedef enum
{
    emLogChanRejectUnspecified,
    emLogChanRejectUnsuitableReverseParameters,
    emLogChanRejectDataTypeNotSupported,
    emLogChanRejectDataTypeNotAvailable,
    emLogChanRejectUnknownDataType,
    emLogChanRejectDataTypeALCombinationNotSupported,
    emLogChanRejectMulticastChannelNotAllowed,
    emLogChanRejectInsuffientBandwdith,
    emLogChanRejectSeparateStackEstablishmentFailed,
    emLogChanRejectInvalidSessionID,
    emLogChanRejectMasterSlaveConflict,
    emLogChanRejectWaitForCommunicationMode,
    emLogChanRejectInvalidDependentChannel,
    emLogChanRejectReplacementForRejected
}emlogChannelRejectCause;

//֧��ý�崩Խ
typedef enum
{
	emNotSupportNATFWTraversal,			//��֧��460��Խ
	emSupportNATFWTraversal,			//֧��460
	emSupportTransmitMulti,			    //֧�ֶ˿ڸ���
	emSupportMediaTraversal				//����Ϊ460������
}emNATFWTraversal;

// ���س���
enum AdpSwitchConstant
{
	Adp_turn_on,		//����
	Adp_turn_off		//�ر�
};

// ��ѯ����
enum AdpPollType
{
	Adp_poll_none,		//û����ѯ
	Adp_poll_vcb,		//�����㲥
	Adp_poll_vcs		//����ѡ��
};

enum AdpPollStatus
{
	Adp_poll_status_none,    //δ��ѯ
	Adp_poll_status_normal,  //��ѯ������
	Adp_poll_status_pause    //��ѯ��ͣ
};

//�������ͺ궨��
enum AdpOprType
{
    Adp_opr_start,
	Adp_opr_stop
};

//MCU�����ն˵��Զ���֪ͨ��Ϣ ��Ϣ��Ŷ���
enum AdpMcu2MtNtfMsgType
{
    emAdpNoneNtf           = 0,
	emAdpBePolledNextNtf   = 1           //��������ѯ�� ֪ͨ
};

///////////////////////////////// �����ṹ ////////////////////////////////
//userInput�ṹ
typedef struct tagUserInputInfo 
{
    s8  m_chSignalType;     //FROM ("0123456789#*ABCD!")
    s32 m_nDuration;        //��ʱֵ����λ��milliseconds

    tagUserInputInfo()
    {
        m_chSignalType = '\0';
        m_nDuration = 300;
    }

    void SetSignalType(s8 signalType)
    {
        m_chSignalType = signalType;
    }

    s8 GetSignalType()
    {
        return m_chSignalType;
    }

    void SetDuration(s32 duration)
    {
        m_nDuration = duration;
    }

    u16 GetDuration()
    {
        return m_nDuration;
    }
}TUserInputInfo,*PTUserInputInfo;
typedef struct tagH460Features
{
	BOOL m_bPeerSupportH460;
	BOOL m_bPeerMediaTraversalServer;
	BOOL m_bPeerSupportTransMultiMedia;
	tagH460Features()
	{
		m_bPeerSupportH460 = FALSE;
		m_bPeerMediaTraversalServer = FALSE;
		m_bPeerSupportTransMultiMedia = FALSE;
	}
}TH460Features,*PTH460Features;


//������ַ
typedef struct tagALIASADDR
{
	AliasType  m_emType;
	s8		   m_achAlias[LEN_ALIAS+2];			//h323-Id ��������λΪ��

	tagALIASADDR()
	{
		Clear();
	}

	void Clear()
	{
		m_emType = type_aliastype;
		memset( m_achAlias, 0, sizeof(m_achAlias) );
	}

	//���ñ���
	BOOL SetAliasAddr( AliasType aliasType, const char* pAlias )
	{
		if ( aliasType <= type_aliastype || aliasType >= type_others ||
			 pAlias == NULL ) 
			return FALSE;
		
		memset( m_achAlias, 0, sizeof(m_achAlias) );

		m_emType = aliasType;

		u16 nLen = min( strlen(pAlias), LEN_ALIAS );
		strncpy( m_achAlias, pAlias, nLen );
		m_achAlias[nLen] = '\0';

		return TRUE;
	}	
	//���type
	AliasType GetAliasType()
	{
		return m_emType;
	}
	//��ñ���
	s8* GetAliasName()  
	{
		return m_achAlias;	
	}
}TALIASADDR,*PTALIASADDR;

//�ؼ����ò�������
typedef struct tagConfigs
{
	u32				m_dwSystem_maxCalls;				    //��������
	u32				m_dwSystem_maxChannels;					//ÿ�����д򿪵��߼�ͨ����
	
	emEndpointType  m_emTerminalType;						//�ն�������(emMt emMcu)
	BOOL			m_bRas_manualRAS;						//�Ƿ��ֶ�RAS����
	BOOL			m_bRas_manualRegistration;				//�Ƿ��ֶ�RASע��
	s8				m_achRas_defaultGkIp[4];				//ȱʡgk��ַ
	u16				m_wRas_defaultGkPort;					//ȱʡgk���ж˿�
	u16				m_wRas_defaultlocalPort;				//ȱʡ����RAS�˿�
	s8				m_ach_UserName[REG_NAME_LEN];			//ע���ʺ�(E164)
	s8				m_ach_Password[REG_PWD_LEN];			//ע����Կ
	
	s32				m_nProductIdSize;
	u8				m_abyProductId[LEN_256];				//��Ʒ��
	s32				m_nVerIdSize;
	u8				m_abyVersionId[LEN_256];				//�汾��
	TALIASADDR		m_atAlias[type_others];					//��������
		
	u16				m_wQ931_CallingPort;					//h225���ж˿�
	emMsTerminalType  m_emMsTerminalType;					//���Ӿ����ն�����   
	BOOL			m_bH245_masterSlaveManualOperation;		//�Ƿ��ֹ���������ȷ��
	BOOL			m_bH245_capabilitiesManualOperation;	//�Ƿ�����ֹ���������

    s32             m_nPortFrom;                            //�˿ڷ�Χ
    s32             m_nPortTo;                              //
	
	u32				m_dwStackIp;							//Э��ջ����IP��������;

	//add by yj for ipv6
	u8          m_byIPType;                                 // ֧�ֵ� IP��ַ����
	u8          m_dwStackIp_ipv6[IPV6_NAME_LEN];			//Э��ջ����IP(ipv6), ��������;
	u8			m_achRas_defaultGkIp_ipv6[IPV6_NAME_LEN];	//ȱʡgk��ַ(IPv6), ��������
//	u8          m_dwStackIp_ipv6[16];			            //Э��ջ����IP(ipv6)��������;
	s16         m_swScopeId;                                 //��ȡ������ IPv6 ��ַ��Χ��ʶ��

	//end
	
	tagConfigs()
	{
		Clear();
	}

	void Clear()
	{
		m_dwSystem_maxCalls = MAX_CALL_NUM;
		m_dwSystem_maxChannels = MIN_CHANNEL_NUM;
		m_bRas_manualRAS = TRUE;
		m_bRas_manualRegistration = TRUE;
		m_wRas_defaultGkPort = RASPORT;
		m_wRas_defaultlocalPort = RASPORT;
		m_wQ931_CallingPort = CALLPORT;
		m_bH245_masterSlaveManualOperation = TRUE;
		m_bH245_capabilitiesManualOperation = TRUE;

		memset(m_atAlias, 0, sizeof(m_atAlias));
		memset(m_ach_UserName, 0, sizeof(m_ach_UserName));
		memset(m_ach_Password, 0, sizeof(m_ach_Password));
		m_emTerminalType  = emEndpointTypeMT;
		m_emMsTerminalType = emMsMT;
		m_nProductIdSize  = 0;
		m_nVerIdSize      = 0;
		memset(m_abyProductId, 0, sizeof(m_abyProductId));
		memset(m_abyVersionId, 0, sizeof(m_abyVersionId));
		m_achRas_defaultGkIp[0] = 127;
		m_achRas_defaultGkIp[1] = 0;
		m_achRas_defaultGkIp[2] = 0;
		m_achRas_defaultGkIp[3] = 1;

        m_nPortFrom = 0;
        m_nPortTo   = 0;

		m_dwStackIp = 0;

		//add by yj for ipv6
		m_byIPType = TYPE_NONE;   
		memset(m_dwStackIp_ipv6, 0, sizeof(m_dwStackIp_ipv6));
		m_swScopeId = -1;
		//end
       

	};

	//������������������߼�ͨ����
	void SetMaxNum( u32 dwMaxCalls, u32 dwMaxChannels )
	{
        m_dwSystem_maxCalls = (dwMaxCalls>MIN_CALL_NUM && dwMaxCalls<MAX_CALL_NUM)?dwMaxCalls:MAX_CALL_NUM;
        m_dwSystem_maxChannels = (dwMaxChannels>MIN_CHANNEL_NUM && dwMaxChannels<MAX_CHANNEL_NUM)?dwMaxChannels:MIN_CHANNEL_NUM;
	}
	//��ȡ��������
	u32 GetMaxCalls()
	{
		return m_dwSystem_maxCalls;
	}
	//��ȡ���ͨ����
	u32 GetMaxChannels()
	{
		return m_dwSystem_maxChannels;
	}
	//�����Ƿ�ʹ���ֶ�RAS
	void SetMannualRAS( BOOL bManualRAS, BOOL bManualReg )
	{
		m_bRas_manualRAS = bManualRAS;
		m_bRas_manualRegistration = bManualReg;
	}
	//��ȡ�Ƿ��ֶ�RAS
	BOOL IsManualRAS()
	{
		return m_bRas_manualRAS;
	}
	//��ȡ�Ƿ��ֶ�ע��
	BOOL IsManualReg()
	{
		return m_bRas_manualRegistration;
	}
	//�����ն����͡����Ӿ����ն�����
	void SetTerminalType( emEndpointType emEpType, emMsTerminalType emMSTType )
	{
		m_emTerminalType = emEpType;
		m_emMsTerminalType = emMSTType;
	}
	//��ȡ�ն�����
	emEndpointType GetEndpointType()
	{
		return m_emTerminalType;
	}
	//��ȡ���Ӿ������ն�����
	emMsTerminalType GetMsTerminalType()
	{
		return m_emMsTerminalType;
	}
	//���ò�Ʒ��
	void SetProductId(u8 *pbyId, s32 nLen)
	{
		if(pbyId == NULL|| nLen <= 0 )
		{
			return ;
		}
		memset( m_abyProductId, 0, sizeof(m_abyProductId) );
		s32 nReal = min(max(LEN_1, nLen), LEN_256);
		m_nProductIdSize = nReal;
        if(nLen >= LEN_1)
		{
			memcpy(m_abyProductId, pbyId, nReal);
		}
	}
	//��ȡ��Ʒ�ų���
	s32 GetProductIdSize()
	{
		return m_nProductIdSize;
	}
	//��ȡ��Ʒ��
	s32 GetProductId(u8 *pbyId, s32 nLen)
	{
		if(pbyId == NULL|| nLen <= 0 )
		{
			return 0;
		}
		s32 nReal = min(nLen, m_nProductIdSize); 
		memcpy(pbyId, m_abyProductId, nReal);
		return nReal;
	}
	//���ð汾��	
	void SetVersionId(u8 *pbyId, s32 nLen)
	{
		if(pbyId == NULL|| nLen <= 0 )
		{
			return ;
		}
		memset( m_abyVersionId, 0, sizeof(m_abyVersionId) );
		s32 nReal = min(max(LEN_1, nLen), LEN_256);
		m_nVerIdSize = nReal;
        if(nLen >= LEN_1)
		{
			memcpy(m_abyVersionId, pbyId, nReal);
		}
	}
	//��ȡ�汾�ų���
	s32 GetVersionIdSize()
	{
		return m_nVerIdSize;
	}
	//��ȡ�汾��
	s32 GetVersionId(u8 *pbyId, s32 nLen)
	{
		if(pbyId == NULL|| nLen <= 0 )
		{
			return 0;
		}
		s32 nReal = min(nLen, m_nVerIdSize); 
		memcpy(pbyId, m_abyVersionId, nReal);
		return nReal;
	}
	//�����û�����
	void SetUserInfo(s8* pszUserName, s8* pszPassword)
	{
		if (pszUserName == NULL)
		{
			return;
		}
		memset(m_ach_UserName, 0, sizeof(m_ach_UserName));
		u16 nameLen = min( strlen(pszUserName), REG_NAME_LEN);
		strncpy(m_ach_UserName, pszUserName, nameLen);
		m_ach_UserName[nameLen] = '\0';

		if (pszPassword)
		{
			memset(m_ach_Password, 0, sizeof(m_ach_Password));
			u16 pwdLen = min(strlen(pszPassword), REG_PWD_LEN);
			strncpy(m_ach_Password, pszPassword, pwdLen);
			m_ach_Password[pwdLen] = '\0';
		}

	}
	//ȡ�û���
	s8* GetUserName()
	{
		return m_ach_UserName;
	}
	//ȡ����
	s8* GetPassword()
	{
		return m_ach_Password;
	}

	//����ȱʡGK��ַ
	void SetDefGKIP(u32 dwGkIP, u16  wGkPort = RASPORT)
	{
		s8 *p = (s8 *)(&dwGkIP);
		memset(m_achRas_defaultGkIp, 0, sizeof(m_achRas_defaultGkIp));
		for(s32 nIndex=0; nIndex<4; nIndex++)
        {
            m_achRas_defaultGkIp[nIndex] = *(p+nIndex);			
        }
		m_wRas_defaultGkPort = wGkPort;
		m_byIPType = TYPE_IPV4;
	}
	//��ȡȱʡGK��ַ
	u32 GetDefGKIP()
	{
		u32 dwGkIP = 0;
		s8 *p = (s8 *)(&dwGkIP);
		for(s32 nIndex=0; nIndex<4; nIndex++)
        {
			*(p+nIndex) = m_achRas_defaultGkIp[nIndex];
        }
		return dwGkIP;
	}
	//��ȡȱʡGK�˿�
	u16 GetDefGKPort()
	{
		return m_wRas_defaultGkPort;
	}

	//���ñ���
	void SetAliasAddr( TALIASADDR &tAliasAddr, u32 dwAliasNo )
	{
		if ( dwAliasNo >= type_others )
		{
			return;
		}
		m_atAlias[dwAliasNo] = tAliasAddr;
	}
	//��ȡ��������
	PTALIASADDR GetAliasAddr( u32 dwAliasNo )
	{
		if ( dwAliasNo >= type_others )
		{
			return NULL;
		}
		return &(m_atAlias[dwAliasNo]);
	}

	//����h225���ж˿�
	void SetH225CallingPort( u16 wCallPort = CALLPORT )
	{
		m_wQ931_CallingPort = wCallPort;
	}
	//��ȡh225���ж˿�
	u16 GetH225CallingPort()
	{
		return m_wQ931_CallingPort;
	}
    //���ñ���RAS�˿�
    void SetLocalRASPort( u16 wRASPort = RASPORT )
    {
        m_wRas_defaultlocalPort = wRASPort;
    }
    //��ȡ����RAS�˿�
    u16 GetLocalRASPort()
    {
        return m_wRas_defaultlocalPort;
    }
	//�����Ƿ��ֶ�MSD��CSE
	void SetH245IsManual( BOOL bMsdManual, BOOL bCseManual )
	{
		m_bH245_masterSlaveManualOperation  = bMsdManual;
		m_bH245_capabilitiesManualOperation = bCseManual;
	}
	//��ȡMSD�Ƿ��ֶ�����
	BOOL IsMasterSlaveManual()
	{
		return m_bH245_masterSlaveManualOperation;
	}
	//��ȡCSE�Ƿ��ֶ�����
	BOOL IsCapabilitiesManual()
	{
		return m_bH245_capabilitiesManualOperation;
	}
    //���ö˿ڷ�Χ
    void SetPortRange(s32 portFrom, s32 portTo)
    {
        m_nPortFrom = portFrom;
        m_nPortTo   = portTo;
    }
    //�õ���ʼ�˿ں�
    s32 GetFirstPort()
    {
        return m_nPortFrom;
    }
    //�õ����һ���˿ں�
    s32 GetLastPort()
    {
        return m_nPortTo;
    }

//add by yj for ipv6
	//����ip��ַ����
	u8 GetStackIP_Type( )
	{
		return	m_byIPType;
	}
//	void SetStackIP_Type(u8 byIPType)
//	{
//		m_byIPType = byIPType;
//	}
	//����ScopeId(ipv6)ֵ
	s16 GetStackIP_Ipv6_ScopeId( )
	{
		return	m_swScopeId;
	}
//	void SetStackIP_Ipv6_ScopeId(s16 swScopeId)
//	{
//		m_swScopeId = swScopeId;
//	}

	//����Э��ջ����IP(ipv6)
	void SetStackIP_Ipv6(u8 *dwIP_ipv6,s16 swScopeId)
	{
		memcpy(m_dwStackIp_ipv6, dwIP_ipv6, sizeof(m_dwStackIp_ipv6));	
		m_swScopeId = swScopeId;
        m_byIPType = TYPE_IPV6;
	}
	
	u8* GetStackIP_Ipv6()
	{
		return m_dwStackIp_ipv6;
		
	}
//end

	//����Э��ջ����IP
	void SetStackIP(u32 dwIP)
	{
		m_dwStackIp = dwIP;
        m_byIPType = TYPE_IPV4;
	}
	u32	GetStackIP()
	{
		return m_dwStackIp;
	}
}TH323CONFIG,*PH323TH323CONFIG; 

//h323stack additional config
typedef struct tagAdditionalConfig
{
	u32 m_dwNATAddress;
	
	//����NAT��ַ
	void SetNATAddress(u32 dwNATAddress)
	{
		m_dwNATAddress = dwNATAddress;
	}
	//�õ�NAT��ַ
	u32 GetNATAddress()
	{
		return m_dwNATAddress;
	}
}TAdditionalConfig;

//transport��ַ
typedef struct tagTransportAddress
{
    //add by yj for ipv6
	u8          m_byIPType;                                 //֧�ֵ� IP��ַ����
	u8          m_dwIP_ipv6[IPV6_NAME_LEN];			        //Э��ջ����IP(ipv6)����������;
//	s16         m_swScopeId;                                //��ȡ������ IPv6 ��ַ��Χ��ʶ��
    //end
	u32 m_dwIP;
	u16 m_wPort;
	u8	m_byType;

	tagTransportAddress()
	{
		Clear();
	}

	void Clear()
	{
		m_dwIP	 = 0;
		m_wPort  = 0;
		m_byType = addr_uca;
		//add by yj for ipv6
		m_byIPType = TYPE_NONE;   
	    memset(m_dwIP_ipv6, 0, sizeof(m_dwIP_ipv6));
//		m_swScopeId = -1;
        //end
	}

    void host2net(BOOL bhton)
    {
        if (bhton)
        {
            m_dwIP  = htonl(m_dwIP);
            m_wPort = htons(m_wPort);
        }
        else
        {
            m_dwIP  = ntohl(m_dwIP);
            m_wPort = ntohs(m_wPort);
        }
    }

	//����transport��ַ
	void SetNetAddress(u32 dwIPAddr, u16 wIPPort, u8 byAddrType=addr_uca)
	{
		m_dwIP   = dwIPAddr;
		m_wPort  = wIPPort;
		m_byType = byAddrType;
		m_byIPType = TYPE_IPV4;
	}
	//add by yj for ipv6
	//����ip��ַ����
	void SetIPAddr_Type(u8 byIPType)
	{
		m_byIPType = byIPType;
	}
	u8 GetIPAddr_Type( )
	{
		return	m_byIPType;
	}
	//void SetNetAddress_Ipv6(u8* dwIPAddr_ipv6, u16 wIPPort, s16 swScopeId, u8 byAddrType=addr_uca)
	void SetNetAddress_Ipv6(u8* dwIPAddr_ipv6, u16 wIPPort, u8 byAddrType=addr_uca)
	{
		memcpy(m_dwIP_ipv6, dwIPAddr_ipv6, sizeof(m_dwIP_ipv6));
		m_wPort  = wIPPort;
		m_byType = byAddrType;
		m_byIPType = TYPE_IPV6;
	//	m_swScopeId = swScopeId;
	}
// 	void SetIPAddr_Ipv6_ScopeId(s16 swScopeId)
// 	{
// 		m_swScopeId = swScopeId;
// 	}
	u8 *GetIPAddr_Ipv6()
	{
		return m_dwIP_ipv6;
	}
//	s16 GetIPAddr_Ipv6_ScopeId( )
//	{
//		return	m_swScopeId;
//	}
	//end

	//��ȡIP��ַ
	u32 GetIPAddr()
	{
		return m_dwIP;
	}
	//��ȡ�˿�
	u16 GetIPPort()
	{
		return m_wPort;
	}
	//��ȡ����
	u8 GetNetAddrType()
	{
		return m_byType;
	}
}TNETADDR,*PTNETADDR;

//���е�ַ
typedef struct tagCallAddr
{
private:
	CallAddrType    m_eType;
	TNETADDR		m_tIPAddr;					
	TALIASADDR		m_tAliasAddr;
public:
	tagCallAddr()
	{
		Clear();
	}

	void Clear()
	{
		m_tIPAddr.Clear();
		m_tAliasAddr.Clear();
	}
	
	//����CallAddrType
	void SetCallAddrType(CallAddrType emAddrType)
	{
		m_eType = emAddrType;
	}
	//���CallAddrType
	CallAddrType GetCallAddrType()
	{
		return m_eType;
	}

	//����IP��ַ�Ͷ˿ں�
	void SetIPAddr(u32 dwIp,u16 wPort = 0)
	{
		m_tIPAddr.m_dwIP  = dwIp;
		m_tIPAddr.m_wPort = htons(wPort);
	}	
	//���IP��ַ
	u32 GetIPAddr()  
	{	
		return m_tIPAddr.m_dwIP;	
	}

	//��ö˿ں�
	u16 GetIPPort()  
	{	
		return ntohs( m_tIPAddr.m_wPort );	
	}
	//����Alias��ַ
	void SetAliasAddr( AliasType emAliasType, const s8* sAlias )
	{
		memset( &m_tAliasAddr, 0, sizeof(m_tAliasAddr) );
		m_tAliasAddr.m_emType = emAliasType;

		if ( sAlias != NULL ) 
		{
			u16 wLen = min( strlen(sAlias), LEN_ALIAS );
			strncpy( m_tAliasAddr.m_achAlias, sAlias, wLen );
			m_tAliasAddr.m_achAlias[wLen] = '\0';
		}
	}	
	//���TALIASADDR��type
	AliasType GetAliasType()
	{
		return m_tAliasAddr.m_emType;
	}
	//���TALIASADDR�ı���
	s8* GetAliasName()  
	{
		return m_tAliasAddr.m_achAlias;	
	}	
}TCALLADDR,*PTCALLADDR;

//����ʱ�ı�����ַ
typedef struct tagAliasAddr
{
	CallAddrType    m_emType;		//��������
	TNETADDR		m_tNetAddr;		//IP����ʱʹ��		
	TALIASADDR		m_tAlias;		//��������ʹ��

	tagAliasAddr()
	{
		m_emType = cat_err;
	}

	void Clear()
	{
		m_emType = cat_err;
		m_tNetAddr.Clear();
		m_tAlias.Clear();
	}

	//����ΪIP��ַ����
	void SetIPCallAddr( TNETADDR *pTNetAddr )
	{
		if ( pTNetAddr != NULL )
		{
			m_emType = cat_ip;
			memcpy( &m_tNetAddr, pTNetAddr, sizeof(m_tNetAddr) );
		}		
	}

	//add by yj for ipv6
	//��ȡip��ַ����
	u8 GetIPAddr_Type( )
	{
		if (m_emType == cat_ip) 
		{
		return	m_tNetAddr.GetIPAddr_Type();
		}
		return TYPE_NONE;
	}
	//��ȡ���е�IP(ipv6)��ַ
	u8* GetIPAddr_Ipv6()
	{
		if (m_emType == cat_ip) 
		{
			if (m_tNetAddr.m_byIPType == TYPE_IPV6)
			{
				return m_tNetAddr.GetIPAddr_Ipv6();
			}
		}
		return 0;
	}
//	s16 GetIPAddr_Ipv6_ScopeId()
//	{
//		if (m_emType == cat_ip) 
//		{
//			if (m_tNetAddr.m_byIPType == TYPE_IPV6)
//			{
//				return m_tNetAddr.GetIPAddr_Ipv6_ScopeId();
//			}
//		}
//		return -1;
//	}

	//end

	//��ȡ���е�IP��ַ
	u32 GetIPAddr()
	{
		if (m_emType == cat_ip) 
		{
			//add by yj
			if (m_tNetAddr.m_byIPType == TYPE_IPV4)
			{
				return m_tNetAddr.GetIPAddr();
			}
		    //end
		}
		return 0;
	}

	//��ȡ���еĶ˿�
	u16 GetIPPort()
	{
		if (m_emType == cat_ip) 
		{
			return m_tNetAddr.GetIPPort();
		}
		return 0;
	}
	//����Ϊ������ַ����
	void SetIPCallAddr( TALIASADDR *pAliasAddr )
	{
		if ( pAliasAddr != NULL )
		{
			m_emType = cat_alias;
			memcpy( &m_tAlias, pAliasAddr, sizeof(m_tAlias) );
		}		
	}
	//��ȡ��������
	AliasType GetAliasType()
	{
		if (m_emType == cat_alias)
		{
			return m_tAlias.GetAliasType();
		}
		return type_aliastype;
	}
	//��ȡ����
	s8* GetAliasName()
	{
		if (m_emType == cat_alias)
		{
			return m_tAlias.GetAliasName();
		}
		return NULL;
	}
	//��ȡ��������
	CallAddrType GetCallAddrType()
	{
		return m_emType;
	}
}TAliasAddr,*PTAliasAddr;



//connect��Ϣ����ʱ���ظ��ϲ�Ľṹ
typedef struct tagNodeInfo 
{
    emEndpointType  m_emEndpointType;   
	s32				m_nVenderid;					//����id
	s8				m_chName[LEN_DISPLAY_MAX+1];	//�������
	BOOL			m_bIsEncrypt;					//�Ƿ�֧�ּ���

    //2007.05.30 
	s32				m_nProductIdSize;
	u8				m_abyProductId[LEN_256];				//��Ʒ��
	s32				m_nVerIdSize;
	u8				m_abyVersionId[LEN_256];				//�汾��
    
	u32             m_dwCallRate;						  //��������	(kbps)

	emNATFWTraversal	  m_bySupportMediaTraversal;
	TH460Features		  m_tH460Features;
	
	TAliasAddr			  m_atCallingAliasAddr[type_others+1]; //���б�����ַ(������ַ+IP)
	TAliasAddr			  m_atCalledAliasAddr[type_others+1]; //���б�����ַ(������ַ+IP)

    tagNodeInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_emEndpointType = emEndpointTypeMT;
		m_nVenderid = vendor_KEDA;
   		memset( m_chName, 0, sizeof(m_chName) ); 		
		
		m_bIsEncrypt = FALSE;

		m_nProductIdSize = 0;
		m_nVerIdSize = 0;
        memset(m_abyProductId, 0, sizeof(m_abyProductId));
        memset(m_abyVersionId, 0, sizeof(m_abyVersionId));
		m_bySupportMediaTraversal = emNotSupportNATFWTraversal;
		memset( &m_tH460Features, 0, sizeof(m_tH460Features) );
	}

	//�����ն�����
	void SetEndpointType(emEndpointType emEpType)
	{
		m_emEndpointType = emEpType;
	}
	//��ȡ�ն�����
	emEndpointType GetEndpointType()
	{
		return m_emEndpointType;
	}
	//���ó���ID
	void SetVenderId( s32 nVenderId)
	{
		m_nVenderid = nVenderId;
	}
	//��ȡ����ID
	s32 GetVenderId()
	{
		return m_nVenderid;
	}
	//����display name
	void SetName(s8 *pchName, s32 nLen)
	{
		if (pchName == NULL || nLen <= 0) 
			return;
		s32 realLen = min(nLen,LEN_DISPLAY_MAX);
		strncpy( m_chName, pchName, realLen );
		m_chName[realLen] = '\0';
	}
	//��ȡdisplay name
	s8* GetName()
	{
		return m_chName;
	}
	//�����Ƿ����
	void SetIsEncrypt( BOOL bIsEncrypt )
	{
		m_bIsEncrypt = bIsEncrypt;
	}
	//��ȡ�Ƿ����
	BOOL IsEncrypt()
	{
		return m_bIsEncrypt;
	}

    	//���ò�Ʒ��
	void SetProductId(u8 *pbyId, s32 nLen)
	{
		if(pbyId == NULL|| nLen <= 0 )
		{
			return ;
		}
		memset( m_abyProductId, 0, sizeof(m_abyProductId) );
		s32 nReal = min(max(LEN_1, nLen), LEN_256);
		m_nProductIdSize = nReal;
        if(nLen >= LEN_1)
		{
			memcpy(m_abyProductId, pbyId, nReal);
		}
	}
	//��ȡ��Ʒ�ų���
	s32 GetProductIdSize()
	{
		return m_nProductIdSize;
	}
	//��ȡ��Ʒ��
	s32 GetProductId(u8 *pbyId, s32 nLen)
	{
		if( pbyId == NULL || nLen <= 0 || m_nProductIdSize <= 0 )
		{
			return 0;
		}
		s32 nReal = min(nLen, m_nProductIdSize); 
		memcpy(pbyId, m_abyProductId, nReal);
		return nReal;
	}
	//���ð汾��	
	void SetVersionId(u8 *pbyId, s32 nLen)
	{
		if(pbyId == NULL|| nLen <= 0 )
		{
			return ;
		}
		memset( m_abyVersionId, 0, sizeof(m_abyVersionId) );
		s32 nReal = min(max(LEN_1, nLen), LEN_256);
		m_nVerIdSize = nReal;
        if(nLen >= LEN_1)
		{
			memcpy(m_abyVersionId, pbyId, nReal);
		}
	}
	//��ȡ�汾�ų���
	s32 GetVersionIdSize()
	{
		return m_nVerIdSize;
	}
	//��ȡ�汾��
	s32 GetVersionId(u8 *pbyId, s32 nLen)
	{
		if( pbyId == NULL || nLen <= 0 || m_nVerIdSize <= 0 )
		{
			return 0;
		}
		s32 nReal = min(nLen, m_nVerIdSize); 
		memcpy(pbyId, m_abyVersionId, nReal);
		return nReal;
	}

	void SetSupportMediaTraversal(emNATFWTraversal emNet)
	{
		m_bySupportMediaTraversal = emNet;
	}
	emNATFWTraversal GetSupportMediaTraversal()
	{
		return m_bySupportMediaTraversal;
	}
	void SetH460features( const TH460Features &th460features )
	{
		memcpy( &m_tH460Features, &th460features, sizeof(TH460Features) );
	}
	void GetH460features( TH460Features &th460features )
	{
		memcpy( &th460features, &m_tH460Features, sizeof(TH460Features) );
	}


	//�������б�����ַ	��ΪԴ�˵���Ϣ
	void SetCallingAliasaddr( TAliasAddr &tAliasAddr, u8 addrNo )
	{
		if ( addrNo < type_others+1  )
		{
			m_atCallingAliasAddr[addrNo] = tAliasAddr;
		}
	}
	//��ȡ���б�����ַ
	PTAliasAddr GetCallingAliasaddr( u8 addrNo )
	{
		if ( addrNo < type_others+1  )
		{
			return &(m_atCallingAliasAddr[addrNo]);
		}
		return NULL;
	}
	
	//���ñ��б�����ַ	��ΪĿ�Ķ˵���Ϣ
	void SetCalledAliasAddr( TAliasAddr &tAliasAddr, u8 byAddrNo )
	{
		if ( byAddrNo < type_others+1  )
		{
			m_atCalledAliasAddr[byAddrNo] = tAliasAddr;
		}		
	}
	//��ȡ���б�����ַ
	PTAliasAddr GetCalledAliasAddr( u8 byAddrNo )
	{
		if ( byAddrNo < type_others+1  )
		{
			return &(m_atCalledAliasAddr[byAddrNo]);
		}
		return NULL;
	}


}TNODEINFO,*PTNODEINFO;



//������Ϣ
typedef struct tagConfInfo
{
	u8          m_abyConfId[LEN_GUID];
	TAliasAddr  m_tConfAlias;
	
	tagConfInfo()
	{
		memset( m_abyConfId, 0, sizeof(m_abyConfId) );
	}

	
	void Clear()
	{
		memset( m_abyConfId, 0, sizeof(m_abyConfId) );
		m_tConfAlias.Clear();
	}

	//���û���ID
	void SetConfId( u8 *pbyConfId, u32 dwLen )
	{
		if ( pbyConfId == NULL )
			return;

		u32 realLen = min(dwLen, LEN_GUID);
		memcpy( m_abyConfId, pbyConfId, realLen );
		m_abyConfId[realLen] = '\0';
	}
	//��ȡ����ID
	u8* GetConfId()
	{
		return m_abyConfId;
	}
	
	//����TAliasAddr
	void SetAliasAddr( TAliasAddr &tAliasAddr)
	{
		m_tConfAlias = tAliasAddr;
	}
	//��ȡTAliasAddr
	TAliasAddr& GetAliasAddr()
	{
		return m_tConfAlias;
	}
}TCONFINFO,*PTCONFINFO;

//�ն˱�Ų���
typedef struct tagTerminalLabel 
{
	u8 m_byMcuNo;
	u8 m_byTerNo;

	tagTerminalLabel()
	{
		Clear();		
	}

	void Clear()
	{
		m_byMcuNo = 0xff;
		m_byTerNo = 0xff;
	}

	bool operator ==(tagTerminalLabel& tLabel)
	{
		if (m_byMcuNo == tLabel.m_byMcuNo && m_byTerNo == tLabel.m_byTerNo)
			return true;
		else
			return false;
	}

	bool operator !=(tagTerminalLabel& tLabel)
	{
		if (m_byMcuNo != tLabel.m_byMcuNo || m_byTerNo != tLabel.m_byTerNo)
			return true;
		else
			return false;
	}
    //��Ч�Լ��
	bool IsValid()
	{
		return ( m_byMcuNo < LEN_MTNUM_PERCONF && m_byTerNo < LEN_MTNUM_PERCONF);
	}
    
    //����TerminalLabel
	BOOL SetTerminalLabel( u8 byMcuNo, u8 byTerNo )
	{
		if( byMcuNo < LEN_MTNUM_PERCONF && byTerNo < LEN_MTNUM_PERCONF )
		{
			m_byMcuNo = byMcuNo;
			m_byTerNo = byTerNo;
            return TRUE;
		}
        return FALSE;
	}
    //��ȡTerminalLabel
	void GetTerminalLabel( u8 *pMcuNo, u8 *pTerNo )
	{
		*pMcuNo = m_byMcuNo;
		*pTerNo = m_byTerNo;
	}
    //��ȡmcu���
	u8 GetMcuNo()
	{
		return m_byMcuNo;
	}
    //��ȡ�ն˱��
	u8 GetTerNo()
	{
		return  m_byTerNo;
	}
}TTERLABEL,*PTTERLABEL;

/*add by jason 2004-08-09*/
typedef struct
{
    unsigned char m_abyMacAddress[6];
    unsigned char m_abyTime[8];
    BOOL m_bClock_seq_change;
} uCID;

typedef struct
{
	u32		m_dwStartTime;
	u32		m_dwStartMilliTime;
	u32		m_dwOldMilliTime;
	u8		m_abyLastTime[8];
	BOOL	m_bNotStart;
	BOOL	m_bGenerated;
	uCID	m_tUCID;
	u8  	m_abyCid[16];
	u8  	m_abyOldCid[16];
	u16     m_wClock_seq;
} cidLocalStorage;

u8* GetGUID(void);
//

typedef struct tagMultiPic
{
	u8  m_byMcuNo;
	u8  m_byStyle;//emPicStyle
	TTERLABEL m_tTer[16];
	
	tagMultiPic()
	{
		Clear();
	}

	void Clear()
	{
		m_byMcuNo = 0;
		m_byStyle = 0;
		memset(m_tTer, 0, sizeof(m_tTer));//HuaweiĬ�϶�Ϊ0
	}
	
}TMultiPic, *PTMultiPic;


typedef struct tagChanMultiCast
{
	u8  m_byChanID;    //1��Ƶ��2��Ƶ��3�ڶ�·��Ƶ
	u32 m_dwIP;        //�鲥��ַ
	u16 m_wPort;       //�鲥�˿�
	//add by yj for ipv6
	u8          m_byIPType;                                 //֧�ֵ� IP��ַ����
	u8          m_dwIP_ipv6[IPV6_NAME_LEN];			         //�鲥��ַipv6����������;
	s16         m_swScopeId;                                //��ȡ������ IPv6 ��ַ��Χ��ʶ��
	//end

    tagChanMultiCast()
    {
        Clear();
    }

    void Clear()
    {
        m_byChanID = emChanUnkown;
        m_dwIP = 0;
        m_wPort = 0;
		//add by yj for ipv6
		m_byIPType = TYPE_NONE;   
	    memset(m_dwIP_ipv6, 0, sizeof(m_dwIP_ipv6));
		m_swScopeId = -1;
        //end
    }

    void host2net(BOOL bhton)
    {
        if (bhton)
        {
            m_dwIP  = htonl(m_dwIP);
            m_wPort = htons(m_wPort);
        }
        else
        {
            m_dwIP  = ntohl(m_dwIP);
            m_wPort = ntohs(m_wPort);
        }
    }

    void SetChanID(u8 byChan)
    {
        m_byChanID = byChan;
    }
	
    u8 GetChanID()
    {
        return m_byChanID;
    }

    //add by yj for ipv6
	//����ip��ַ����
	void SetChanAddr_Type (u8 byIPType)
	{
		m_byIPType = byIPType;
	}
	u8 GetChanAddr_Type( )
	{
		return	m_byIPType;
	}
	//����ScopeId(ipv6)ֵ
	s16 GetChanAddr_Ipv6_ScopeId( )
	{
		return	m_swScopeId;
	}
	void SetChanAddr_Ipv6_ScopeId(s16 swScopeId)
	{
		m_swScopeId = swScopeId;
	}
	//����Э��ջ����IP(ipv6)
	void SetChanAddr_Ipv6(u8 *dwIP_ipv6)
	{
		memcpy(m_dwIP_ipv6, dwIP_ipv6, sizeof(m_dwIP_ipv6));	
	}
	u8 *GetChanAddr_Ipv6()
	{
		return m_dwIP_ipv6;
	}
	

	//end

    void SetChanAddr(u32 ip, u16 port)
    {
        m_dwIP = ip;
        m_wPort = port;
    }

    u32 GetChanIp()
    {
        return m_dwIP;
    }

    u16 GeChantPort()
    {
        return m_wPort;
    }
    
}TCHANMULTICAST, *PTCHANMULTICAST;


/*
�������г�������ָʾ

*/
typedef struct tagCapInfo
{   
    s32  m_nVendor;                     //����ID
    BOOL m_bIsMCU;                      //FALSE:MT, TRUE:MCU
    BOOL m_bMix;                        //����
    BOOL m_bVAC;                        //��������
    BOOL m_bCustomVMP;                  //���ƻ���ϳ�
    BOOL m_bAutoVMP;                    //�Զ�����ϳ�
    BOOL m_bEndConf;                    //��������
    BOOL m_bInvateMt;                   //�����ն�
    BOOL m_bDropMt;                     //ɾ���ն�
    BOOL m_bSelSpeaker;                 //ָ��/ȡ��������
    BOOL m_bSelChair;                   //ָ��/������ϯ
    BOOL m_bSelSource;                  //ѡ���ն�
    BOOL m_bFECC;                       //Զ������ͷң��
    BOOL m_bQuiet;                      //Զ�˾���
    BOOL m_bMute;                       //Զ������
    BOOL m_bConfReq;                    //�������봦��
    BOOL m_bOnlineList;                 //�����ն��б�
    BOOL m_bOfflineList;                //�����ն��б�
    BOOL m_bSelSpeakingUser;            //����
    BOOL m_bPicSwitch;                  //���໭���л�
    BOOL m_bMustSeeSpeaker;             //ǿ�ƹ㲥
    //...                                
                            

    tagCapInfo()
    {
        Clear();
    }

    void Clear()
    {
        m_nVendor = vendor_UNKNOWN;
        m_bIsMCU = FALSE;
        m_bMix = FALSE;
        m_bCustomVMP = FALSE;
        m_bAutoVMP = FALSE;
        m_bVAC = FALSE;
        m_bEndConf = FALSE;
        m_bInvateMt = FALSE;
        m_bDropMt = FALSE;
        m_bSelSource = FALSE;
        m_bSelSpeaker = FALSE;
        m_bSelChair = FALSE;
        m_bFECC = FALSE;
        m_bQuiet = FALSE;
        m_bMute = FALSE;
        m_bOnlineList = FALSE;
        m_bOfflineList = FALSE;
        m_bConfReq = FALSE;
        m_bSelSpeakingUser = FALSE;
        m_bPicSwitch = FALSE;
        m_bMustSeeSpeaker = FALSE;
    }

}TCAPINFO, *PTCAPINFO;

/*
�ù�����Ҫ�����ڻ�����A�ն˴Ӵ��ڶ��������� ͨ�����紫����Զ� 
��Ϣ����
  1.��������    //������ 1 -RS232��������  2 =RS422 3=RS485 
  2.���ݳ���
  3.����
*/
typedef struct tagCOMData
{
    emComType  m_emComType;
    s32 m_nDataLen;
    s8  m_achData[128];
    
public:
    tagCOMData()
    {
        Clear();
    }

    void Clear()
    {
        m_emComType = emComUnkown;
        memset(m_achData, 0, sizeof(m_achData));
        m_nDataLen = 0;
    }

    void host2net(BOOL bhton)
    {
        s32 nType = m_emComType;
        if (bhton)
        {
            m_emComType  = (emComType)htonl(nType);
            m_nDataLen   = htonl(m_nDataLen);
        }
        else
        {
            m_emComType  = (emComType)ntohl(nType);
            m_nDataLen   = ntohl(m_nDataLen);
        }
    }

    void SetComType(emComType emType)
    {
        m_emComType = emType;
    }

    emComType GetComType()
    {
        return m_emComType;
    }

    void SetComData(s8 *pData, s32 nLen)
    {
        if (NULL == pData || nLen < 0)
        {
            return;
        }

        m_nDataLen = min(nLen, sizeof(m_achData));
        memset(m_achData, 0, sizeof(m_achData));
        memcpy(m_achData, pData, m_nDataLen);
        m_achData[m_nDataLen] = '\0';
    }

    s32 GetComDataLen()
    {
        return m_nDataLen;
    }

    s8* GetComData()
    {
        return m_achData;
    }

}TCOMDATA, *PTCOMDATA;


//��Ƶ������(����ʾH264������) 
/*********************����֡�ʵ�����******************
*1��ʾ29.97, 2��ʾ29.97/2, 3��ʾ29.97/3,.....
*H261��cif(1-4) qcif(1-4)
*H263: sqcif,qcif,cif,4cif,16cif  (1-32)
*MP2/MP4: cif, 2cif, 4cif 1-30
*****************************************************/
typedef struct tagVideoCap
{
	cmCapDirection  m_emCapDirection;		//transmit or receive
	u16             m_wMaxBitRate;						//��λkbps
	u8              m_abyResolution[emResolutionEnd];	//֡��  	
public:
	tagVideoCap()
	{
		Clear();
	}
	
	void Clear()
	{
		m_emCapDirection = cmCapReceive;
		m_wMaxBitRate = 0;
		memset(m_abyResolution, 0, sizeof(m_abyResolution));        
	}

    void host2net(BOOL bhton)
    {
        s32 nCapDirection = m_emCapDirection;
        if (bhton)
        {
            m_emCapDirection = (cmCapDirection)htonl(nCapDirection);
            m_wMaxBitRate    = htons(m_wMaxBitRate);
        }
        else
        {
            m_emCapDirection = (cmCapDirection)ntohl(nCapDirection);
            m_wMaxBitRate    = ntohs(m_wMaxBitRate);
        }
    }

	//��λkbps
	void SetBitRate(u16 wBitRate)
	{
		m_wMaxBitRate = wBitRate;		
	}
	u16 GetBitRate() const
	{
        return m_wMaxBitRate;
	}

	void SetCapDirection(cmCapDirection emDirect)
	{
		m_emCapDirection = emDirect;
	}
	cmCapDirection GetCapDirection() const
	{
		return m_emCapDirection;
	}

	/*
	 *function: ����֧�ֵķֱ��ʡ�֡��
	 *param:	emRes ��ʾ�ֱ��� byMPI��ʾ֡��,�μ��ṹͷ˵��
     *return:   TRUE or FALSE 
	 */
	BOOL SetResolution(emResolution emRes, u8 byMPI)
	{
		if(emRes <= emResolutionBegin || emRes >= emResolutionEnd)
		{
			return FALSE;
		}
		m_abyResolution[emRes] = byMPI;
	    return TRUE;
	}
    /*
	 *function: �õ�֧�ֵķֱ��ʡ�֡��
	 *param:	emRes ��ʾ�ֱ��� byMPI��ʾ֡��,�μ��ṹͷ˵��
     *return:   ֡��(0 ��ʾ��֧�ָķֱ���)  
	 */
	u8 GetResolution(emResolution emRes) const
	{
		if(emRes <= emResolutionBegin || emRes >= emResolutionEnd)
		{
			return 0;
		}
		return m_abyResolution[emRes];
	}
	
	void MergeVideoCap( const tagVideoCap &tVideoCap )
	{
		if (m_wMaxBitRate != 0)
		{
			m_wMaxBitRate = min( m_wMaxBitRate, tVideoCap.m_wMaxBitRate );
		}
		else
		{
			m_wMaxBitRate = tVideoCap.m_wMaxBitRate;
		}
		m_emCapDirection = tVideoCap.m_emCapDirection;
		for ( int nIndex = emResolutionBegin +1; nIndex < emResolutionEnd; ++nIndex )
		{
			if ( m_abyResolution[nIndex] == 0 )
			{
				m_abyResolution[nIndex] = tVideoCap.m_abyResolution[nIndex];
			}
		}
	}
}TVideoCap;

//H.264��Ƶ������
/*********************����֡�ʵ�����******************
*1��ʾ1fps, 60����60fps���������֡�ʿ��Դﵽ����ֵ255
*****************************************************/
typedef struct tagH264VideoCap
{
public:
    // Э�� 
    enum  emH264ProfileMask
    {
        emProfileBaseline   = 64,
        emProfileMain       = 32,
        emProfileExtend     = 16,
        emProfileHigh       = 8
    };

    tagH264VideoCap()
    {
        Clear();
    }
    
    void Clear()
    {
        memset(this, 0, sizeof(tagH264VideoCap));
        m_emCapDirection = cmCapReceive;
        m_wMaxBitRate = 0;
        SetSupportProfile(emProfileBaseline);
        m_byLevel = 36;  //level 1.3 
		m_nParaFlag = 0;
        m_nMaxBRandCPB = 0;
    }
    
    void host2net(BOOL bhton)
    {
        s32 nCapDirection = m_emCapDirection;
        if (bhton)
        {
            m_emCapDirection = (cmCapDirection)htonl(nCapDirection);
            m_wMaxBitRate    = htons(m_wMaxBitRate);
            m_nMaxMBPS       = htonl(m_nMaxMBPS);
            m_nMaxFS         = htonl(m_nMaxFS);
            m_nMaxDPB        = htonl(m_nMaxDPB);
            m_nMaxBRandCPB   = htonl(m_nMaxBRandCPB);
            m_nMaxStaticMBPS = htonl(m_nMaxStaticMBPS);
            m_nParaFlag      = htonl(m_nParaFlag);
        }
        else
        {
            m_emCapDirection = (cmCapDirection)ntohl(nCapDirection);
            m_wMaxBitRate    = ntohs(m_wMaxBitRate);
            m_nMaxMBPS       = ntohl(m_nMaxMBPS);
            m_nMaxFS         = ntohl(m_nMaxFS);
            m_nMaxDPB        = ntohl(m_nMaxDPB);
            m_nMaxBRandCPB   = ntohl(m_nMaxBRandCPB);
            m_nMaxStaticMBPS = ntohl(m_nMaxStaticMBPS);
            m_nParaFlag      = ntohl(m_nParaFlag);
        }
    }        

    // ���䷽����
    void SetCapDirection(cmCapDirection emDirect)
    {
        m_emCapDirection = emDirect;
    }
    cmCapDirection GetCapDirection() const
    {
        return m_emCapDirection;
	}

    // ͨ������
    void SetBitRate(u16 wBitrate)
    {
        m_wMaxBitRate = wBitrate;
    }
    
    u16  GetBitRate() const
    {
        return m_wMaxBitRate;
    }

    // Э��: ֧�� emH264ProfileMask �������������ǵ��߼���
    void SetSupportProfile(u8 byProfile)
    {
        m_byProfile = byProfile;
// 		if(m_byProfile < 64)
// 			m_byProfile = 64;
    }

    BOOL IsSupportProfile(u8 byReqProfile) const
    {
        return ((m_byProfile&byReqProfile) == byReqProfile);
    }

    u8   GetProfileValue() const   
    {
        return m_byProfile;
    }
    
    // ����������

	/*
	 *function: ��ȡ�ض��ֱ����µ�֡��
	 *param:	u8 byRes                    �ֱ��ʣ�emResolution ���� emResolutionHD
     *return:   u8 ֡�� frame/s
	 */
    inline u8   GetResolution(u8 byRes) const;
    inline u8   GetResolution(u16 wWidth, u16 wHeight) const;

	/*
	 *function: �ض��ֱ����£��ض�֡��(���ڳ�ģʽ����Ҫ�ϲ�ת��Ϊ֡�ʴ���)�Ƿ�֧��
                ���ڶԶ��Ƿ�֧�ֳ���ʽ��Ҫҵ����� IsSupportProfile �����ж� 
	 *param:	u8 byRes                    �ֱ��ʣ�emResolution ���� emResolutionHD
                u8 byFps                    ֡��frame/s
     *return:   TRUE/FALSE
	 */
    inline BOOL IsSupport(u8 byRes, u8 byFps) const;
    inline BOOL IsSupport(u16 wWidth, u16 wHeight, u8 byFps) const;

	/*
	 *function: ����֧��ĳ�ֱַ��ʺ�֡��(���ڳ�ģʽ����Ҫ�ϲ�ת��Ϊ֡�ʴ���)�����ֱַ��ʿ��Ե�������
	 *param:	u8 byRes                    �ֱ��ʣ�emResolution ���� emResolutionHD
                u8 byFps                    ֡��frame/s
	 */
    inline void  SetResolution(u8 byRes, u8 byFps) ;
    inline void  SetResolution(u16 wWidth, u16 wHeight, u8 byFps) ;

    // �ڲ�ʹ�ú���
    void  SetMaxMBPS(s32 nMax)
    {
        m_nMaxMBPS = nMax;
    }
    s32   GetMaxMBPS() const
    {
        return m_nMaxMBPS;
    }
    void  SetMaxFS(s32 nMax)
    {
        m_nMaxFS = nMax;
    }
    s32   GetMaxFS() const
    {
        return m_nMaxFS;
    }
	void  SetMaxBRandCPB(s32 nMaxBRandCPB)
	{
		m_nMaxBRandCPB = nMaxBRandCPB;
	}
	s32   GetMaxBRandCPB() const
	{
		return m_nMaxBRandCPB;
	}

    //  Level���ⲿ������Ч
    void SetLevel(u8 byLevel)
    {
        m_byLevel = byLevel;
    }
    u8 GetLevel() const
    {
        return m_byLevel;
    }

	s32 GetParaFlag()
	{
		return m_nParaFlag;
	}
    void SetParaFlag(s32 nParaFlag)
    {
        m_nParaFlag = nParaFlag;
    }

	void SetMaxStaticMBPs( s32 nStaticMBPs )
	{
		m_nMaxStaticMBPS = nStaticMBPs;
	}
	s32 GetMaxStaticMBPs() const
	{
		return m_nMaxStaticMBPS;
	}

    // toolkit: Res enum to width*height
    inline void  Res2WxH(u8 byRes, u16 &wWidth, u16 &wHeight) const;

	BOOL operator <= (const tagH264VideoCap& tH264VideoCap)
	{
		if((m_nMaxMBPS <= tH264VideoCap.GetMaxMBPS()) && (m_nMaxFS <= tH264VideoCap.GetMaxFS()) && (( m_byProfile | tH264VideoCap.GetProfileValue() ) == tH264VideoCap.GetProfileValue()) )
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}

	void operator = (const tagH264VideoCap& tH264VideoCap)
	{
		memcpy(this, (void*)&tH264VideoCap, sizeof(tH264VideoCap));
	}

	BOOL operator == (const tagH264VideoCap& tH264VideoCap)
	{
        if(memcmp(this, (void*)&tH264VideoCap, sizeof(tH264VideoCap)) == 0)
		    	return TRUE;

		return FALSE;
	}

protected:
    cmCapDirection  m_emCapDirection;		            //transmit or receive
    u16             m_wMaxBitRate;						//��λkbps

    // H.264 �������壬�μ� ITU H.241�ĵ�
    u8              m_byProfile;
    u8              m_byLevel;
    // ����2���ֶΣ�ȡ Custom ��LevelֵĬ�ϵ� max(��λ��Ϊ���)
    s32             m_nMaxMBPS;
    s32             m_nMaxFS;
    // ���±�����Ǿ��� Custom ���ֶΣ���ʱ��֧�����ã�
    s32             m_nMaxDPB;
    s32             m_nMaxBRandCPB;
    s32             m_nMaxStaticMBPS;

	// �����Ǳ�־�ֶ�,�������ƫ����Ӧλ��λ
	s32             m_nParaFlag;

}TH264VideoCap;

// sif/cif ���²�֧��
inline void TH264VideoCap::Res2WxH(u8 byRes, u16 &wWidth, u16 &wHeight) const
{
    switch (byRes)
    {
    case emCIF:
        wWidth = 352;   wHeight = 288;   break;
    case emCIF2:
        wWidth = 576;   wHeight = 352;   break;
    case emCIF4:
        wWidth = 704;   wHeight = 576;   break;
    case em352240:
        wWidth = 352;   wHeight = 240;   break;
    case em704480:
        wWidth = 704;   wHeight = 480;   break;
    case em640480:
        wWidth = 640;   wHeight = 480;   break;
    case em800600:
        wWidth = 800;   wHeight = 600;   break;
    case em1024768:
        wWidth = 1024;  wHeight = 768;   break;
    case emW4CIF:
        wWidth = 1024;  wHeight = 576;   break;
    case emHD720:
        wWidth = 1280;  wHeight = 720;   break;
    case emSXGA:
        wWidth = 1280;  wHeight = 1024;  break;
    case emUXGA:
        wWidth = 1600;  wHeight = 1200;  break;
    case emHD1080:
        wWidth = 1920;  wHeight = 1080;  break;
	case em1280x768:
		wWidth = 1280;  wHeight = 768;   break;
	case em1280x800:
		wWidth = 1280;  wHeight = 800;   break;
	case em1366x768:
		wWidth = 1366;  wHeight = 768;   break;
	case emQCIF:
		wWidth = 176;  wHeight = 144;   break;
	case emSQCIF:
		wWidth = 128;  wHeight = 96;   break;
    default:
        wWidth = 352;   wHeight = 288;   break;     // default as cif
    }

    return;
}
inline u8 TH264VideoCap::GetResolution(u8 byRes) const
{
    u16 wWidth = 0;
    u16 wHeight = 0;
    Res2WxH(byRes, wWidth, wHeight);

    return GetResolution(wWidth, wHeight);
}

#define BYTE_CUTTER(n)  ( n>0xFF ? 0xFF : ( (n==11 || n==12 || n==14 || n==24 || n==29 || n==59) ? n+1 : n )  ) 
inline u8 TH264VideoCap::GetResolution(u16 wWidth, u16 wHeight) const
{    
    if (wWidth*wHeight > (m_nMaxFS)<<8)
    {
        return 0;
    }

	int nFps = 0;
	s32 nMaxFs = (wWidth*wHeight)>>8;;
	if ( ((nMaxFs>>8)<<8) < nMaxFs )
	{
		nMaxFs = (nMaxFs>>8) + 1;
		nMaxFs = nMaxFs << 8;
    }
	double dabs = (nMaxFs) - (m_nMaxFS);
	if ( m_nMaxStaticMBPS != 0 && fabs( dabs ) <= 2.0 )
	{
		double dMaxMBPS = m_nMaxMBPS;//GetMaxMBPS();
		double dMaxFS = m_nMaxFS;//GetMaxFS();
		double dMaxStaticMBPS = m_nMaxStaticMBPS;//GetMaxStaticMBPs();
		s32 nNewMaxMBPS = (s32)(1.0 / ( ( ( 4.0 / dMaxFS ) / dMaxMBPS ) + ( ( ( dMaxFS - 4.0 ) / dMaxFS ) / dMaxStaticMBPS ) ));
		nFps = (nNewMaxMBPS<<8) / (wWidth*wHeight);
	} 
	else
	{
		nFps = (m_nMaxMBPS<<8) / (wWidth*wHeight);
	}

    //return BYTE_CUTTER(nFps);
	if( nFps > 0xFF )
		nFps = 0xFF;
	return nFps;

}
#undef BYTE_CUTTER

inline BOOL TH264VideoCap::IsSupport(u8 byRes, u8 byFps) const
{
    return GetResolution(byRes) >= byFps;
}

inline BOOL TH264VideoCap::IsSupport(u16 wWidth, u16 wHeight, u8 byFps) const
{
    return GetResolution(wWidth, wHeight) >= byFps;
}

inline void TH264VideoCap::SetResolution(u8 byRes, u8 byFps)
{
    u16 wWidth = 0;
    u16 wHeight = 0;
    Res2WxH(byRes, wWidth, wHeight);
    
    SetResolution(wWidth, wHeight, byFps);
}
inline void TH264VideoCap::SetResolution(u16 wWidth, u16 wHeight, u8 byFps)
{
	//                       1  1.1 1.2 1.3 2.1 2.2 3   3.1 3.2  4  4.2   5   5.1
	const u8 abyLevel[13] = {15, 22, 29, 36, 50, 57, 64, 71, 78, 85, 99, 106, 113};

    const s32 MaxMBPSAndMaxFrame[13][2] = {{1485,99},{3000,396},{6000,396},{11880,396},{19800,792},{20250,1620},{40500,1620},
											{108000,3600},{216000,5120},{245760,8192},{522240,8704},{589824,22080},{983040,36864}};

    s32 nNewMaxFs = (wWidth*wHeight)>>8;
    if (nNewMaxFs > m_nMaxFS)
    {
        m_nMaxFS = nNewMaxFs;
        if ( ((m_nMaxFS>>8)<<8) < m_nMaxFS )
        {
            m_nMaxFS = (m_nMaxFS>>8) + 1;
			m_nMaxFS = m_nMaxFS << 8;
        }
    }
    s32 nNewMaxMBPS = nNewMaxFs*byFps;
    if (nNewMaxMBPS > m_nMaxMBPS)
    {
        m_nMaxMBPS = nNewMaxMBPS;
        if ( (m_nMaxMBPS/500*500) < m_nMaxMBPS )
        {
            m_nMaxMBPS = m_nMaxMBPS/500 + 1;
			m_nMaxMBPS = m_nMaxMBPS * 500;
        }
    }

	for(s32 i=0; i<13; i++)
	{
		if(m_nMaxMBPS >= MaxMBPSAndMaxFrame[i][0] && m_nMaxFS >= MaxMBPSAndMaxFrame[i][1])
		{
			m_byLevel = abyLevel[i];
			m_nParaFlag = 0;
			if(m_nMaxMBPS > MaxMBPSAndMaxFrame[i][0])
				m_nParaFlag = 1;
			if(m_nMaxFS > MaxMBPSAndMaxFrame[i][1])
				m_nParaFlag = m_nParaFlag | 2;
		}
		else
		{
			break;
		}
	}

    // cif*30���²�֧��
// 	if(m_byLevel < 36)
// 	{
// 		m_byLevel = 36;
// 		m_nParaFlag = 0;
// 		if(m_nMaxMBPS > MaxMBPSAndMaxFrame[3][0])
// 		{
// 			m_nParaFlag = 1;
// 		}
// 		else
// 		{
// 			m_nMaxMBPS = MaxMBPSAndMaxFrame[3][0];
// 			if ( (m_nMaxMBPS/500*500) < m_nMaxMBPS )
// 			{
// 				m_nMaxMBPS = m_nMaxMBPS/500 + 1;
// 				m_nMaxMBPS = m_nMaxMBPS * 500;
// 			}
// 		}
// 		if(m_nMaxFS > MaxMBPSAndMaxFrame[3][1])
// 		{
// 			m_nParaFlag = m_nParaFlag | 2;
// 		}
// 		else
// 		{
// 			m_nMaxFS = MaxMBPSAndMaxFrame[3][1];
// 			if ( ((m_nMaxFS>>8)<<8) < m_nMaxFS )
// 			{
// 				m_nMaxFS = (m_nMaxFS>>8) + 1;
// 				m_nMaxFS = m_nMaxFS << 8;
// 			}
// 		}
// 	}
}

//��Ƶ��������������G.7231
typedef struct tagAudioCap
{
	cmCapDirection  m_emCapDirection; //transmit or receive
	u8              m_byPackTime;     //ÿһRTP�������ʱ��,��λms(1-256); 
public:
	tagAudioCap()
	{
		Clear();
	}

	void Clear()
	{
		m_emCapDirection = cmCapReceive;
		m_byPackTime = 60;
	};

    void host2net(BOOL bhton)
    {
        s32 nCapDirection = m_emCapDirection;
        if (bhton)
        {
            m_emCapDirection = (cmCapDirection)htonl(nCapDirection);
        }
        else
        {
            m_emCapDirection = (cmCapDirection)ntohl(nCapDirection);
        }
    }

	void SetCapDirection(cmCapDirection emDirect)
	{
		m_emCapDirection = emDirect;
	}
	cmCapDirection GetCapDirection()
	{
		return m_emCapDirection;
	}
    //���ô��ʱ��
	void SetPackTime(u8 byPackTime)
	{
		m_byPackTime = byPackTime;
	}
    //��ȡ���ʱ��
	u8  GetPackTime()
	{
		return m_byPackTime;
	}	
}TAudioCap;

//G7231��������
typedef struct tagG7231Cap
{
	cmCapDirection  m_emCapDirection;		//transmit or receive
	u8				m_byMaxFrameNum;		//��������֡��
	BOOL			m_bSilenceSuppression;	//�Ƿ�������
public:
	tagG7231Cap()
	{
		Clear();
	}

	void Clear()
	{
		m_emCapDirection = cmCapReceive;
		m_byMaxFrameNum  = 1;			    //Ŀǰ����ֻ֧�ֵ�֡
		m_bSilenceSuppression = TRUE;	    //����Ĭ��֧�־�������
	}

    void host2net(BOOL bhton)
    {
        s32 nCapDirection = m_emCapDirection;
        if (bhton)
        {
            m_emCapDirection        = (cmCapDirection)htonl(nCapDirection);
            m_bSilenceSuppression   = htonl(m_bSilenceSuppression);
        }
        else
        {
            m_emCapDirection        = (cmCapDirection)ntohl(nCapDirection);
            m_bSilenceSuppression   = ntohl(m_bSilenceSuppression);
        }
    }

	void SetCapDirection(cmCapDirection emDirect)
	{
		m_emCapDirection = emDirect;
	}
	cmCapDirection GetCapDirection()
	{
		return m_emCapDirection;
	}

    //�����Ƿ�֧�־���
    void SetIsSilenceSuppression(BOOL bSilenceSuppression)
    {
        m_bSilenceSuppression = bSilenceSuppression;
    }
    //�Ƿ�֧�־���
	BOOL IsSilenceSuppression()
	{
		return m_bSilenceSuppression;
	}
    
    //����ÿ�������֡��
	void SetMaxFrameNumPerPack(u8 byMaxFrameNum)
	{
		m_byMaxFrameNum = byMaxFrameNum;
	}
    //��ȡÿ�������֡��
	u8 GetMaxFrameNumPerPack()
	{
		return m_byMaxFrameNum;
	}
}TG7231Cap;

//MPEG AAC������
typedef struct tagAACCap
{
    enum emAACSampleFreq                    //sampling frequency
    {
        emFs96000 = 0,
        emFs88200 = 1,
        emFs64000 = 2,
        emFs48000 = 3,
        emFs44100 = 4,
        emFs32000 = 5,
        emFs24000 = 6,
        emFs22050 = 7,
        emFs16000 = 8,
        emFs12000 = 9,
        emFs11025 = 10,
        emFs8000  = 11
    };
    
    enum emAACChnlCfg                       //channel config
    {
        emChnlCust   = 0,
        emChnl1      = 1,                   //������
        emChnl2      = 2,                   //˫����
        emChnl3      = 4,
        emChnl4      = 8,
        emChnl5      = 16,
        emChnl5dot1  = 32,                   //5.1����
        emChnl7dot1  = 64                    //7.1����
    };

	cmCapDirection  m_emCapDirection;		//transmit or receive    
    emAACSampleFreq m_emSampleFreq;
    emAACChnlCfg    m_emChnlCfg;
    u16             m_wBitrate;
    u8              m_byMaxFrameNum;

public:
    tagAACCap()
    {
        Clear();
    }
    
    void Clear()
    {
        m_emCapDirection = cmCapReceive;
        m_emSampleFreq = emFs32000;
        m_emChnlCfg = emChnlCust;
        m_byMaxFrameNum  = 1;			    //Ŀǰ����ֻ֧�ֵ�֡
        m_wBitrate = 96;                    //kbps
    }
    
    void host2net(BOOL bhton)
    {
        s32 nCapDirection = m_emCapDirection;
        if (bhton)
        {
            m_emCapDirection        = (cmCapDirection)htonl(nCapDirection);
            m_emSampleFreq          = (emAACSampleFreq)htonl(m_emSampleFreq);
            m_emChnlCfg             = (emAACChnlCfg)htonl(m_emChnlCfg);
            m_wBitrate              = htons(m_wBitrate);
        }
        else
        {
            m_emCapDirection        = (cmCapDirection)ntohl(nCapDirection);
            m_emSampleFreq          = (emAACSampleFreq)ntohl(m_emSampleFreq);
            m_emChnlCfg             = (emAACChnlCfg)ntohl(m_emChnlCfg);
            m_wBitrate              = ntohs(m_wBitrate);
        }
    }
    
    void SetCapDirection(cmCapDirection emDirect)
    {
        m_emCapDirection = emDirect;
    }
    cmCapDirection GetCapDirection() const
    {
        return m_emCapDirection;
	}

    void SetSampleFreq(emAACSampleFreq emFs)
    {
        m_emSampleFreq= emFs;
    }

    emAACSampleFreq GetSampleFreq() const
    {
        return m_emSampleFreq;
    }

    void SetChnl(emAACChnlCfg emChnl)
    {
        m_emChnlCfg = emChnl;
    }

    emAACChnlCfg GetChnl() const
    {
        return m_emChnlCfg;
    }

    void SetBitrate(u16 wBitrate) 
    {
        m_wBitrate = wBitrate;
    }

    u16 GetBitrate() const
    {
        return m_wBitrate;
    }
}TAACCap;

//����������
typedef struct tagDataCap
{
	cmCapDirection  m_emCapDirection;				//transmit or receive
	u32             m_dwMaxBitRate;					//��λkbps; 
public:
	tagDataCap()
	{
		Clear();
	}

	void Clear()
	{
		m_dwMaxBitRate = 64;
		m_emCapDirection = cmCapReceiveAndTransmit;//�����ŵ�
	}

    void host2net(BOOL bhton)
    {
        s32 nCapDirection = m_emCapDirection;
        if (bhton)
        {
            m_emCapDirection = (cmCapDirection)htonl(nCapDirection);
            m_dwMaxBitRate   = htonl(m_dwMaxBitRate);
        }
        else
        {
            m_emCapDirection = (cmCapDirection)ntohl(nCapDirection);
            m_dwMaxBitRate   = ntohl(m_dwMaxBitRate);
        }
    }

	void SetCapDirection(cmCapDirection emDirect)
	{
		m_emCapDirection = emDirect;
	}
	cmCapDirection GetCapDirection()
	{
		return m_emCapDirection;
	}

	//��λkbps
	void SetBitRate(u32 dwBitRate)
	{
		m_dwMaxBitRate = dwBitRate;		
	}
	u32 GetBitRate()
	{
        return m_dwMaxBitRate;
	}		
}TDataCap;

//����H460���в���
typedef struct tagH460CallParam 
{
	cmTransportAddress   m_tCallSignalAddr;
	u8                   m_abyCallId[LEN_GUID];      //CallIdentifier

	tagH460CallParam()
	{
		memset(&m_tCallSignalAddr, 0, sizeof(cmTransportAddress));
		memset(m_abyCallId, 0, LEN_GUID);
	}
}TH460CALLPARAM, *PTH460CALLPARAM;
//������в���
typedef struct tagCallParam 
{
	cmConferenceGoalType  m_emConfGoalType;  				  //�����Ŀ������
	cmCallType            m_emCallType;						  //�������� 
	emEndpointType        m_emEndpointType;					  //�ն�����  ��ʾ�����ն˵�����
	u32					  m_dwCallRate;						  //��������	(kbps)
    TAliasAddr			  m_tCalledAddr;					  //���е�ַ�� ����ʱ,������Ϊ������ַ������ʱΪ���������ַ
    TAliasAddr			  m_tCallingAddr;					  //���е�ַ   ���������ַ
	TAliasAddr			  m_atCallingAliasAddr[type_others+1];//���б�����ַ(������ַ+IP) ��ȱʡ���������ļ�������
	TAliasAddr			  m_atCalledAliasAddr[type_others+1]; //���б�����ַ(������ַ+IP)
	u8					  m_abyConfId[LEN_GUID];		      //�����,����16 octet
	u8					  m_abyCallId[LEN_GUID];  
	s8					  m_achDisplay[LEN_DISPLAY_MAX+1];	  //������Ϣ

    //UserInfo�ֶ��ݲ�ʹ��
    s32					  m_nUUSize; 
	u8					  m_abyUserInfo[LEN_USERINFO_MAX];	  //UserInfo��Ϣ���ȣ�2-131�ֽ�

	BOOL				  m_bIsEncrypt;						  //�Ƿ����

    //����ԭ����UserInfo�ֶ�
	s32             m_nNonStandLen;
	u8              m_abyNonStandData[LEN_NONSTANDARD_MAX];
    

    //2007.05.30 
	s32				      m_nProductIdSize;
	u8				      m_abyProductId[LEN_256];				//��Ʒ��
	s32				      m_nVerIdSize;
	u8				      m_abyVersionId[LEN_256];				//�汾��

	emNATFWTraversal	  m_bySupportMediaTraversal;
	TH460Features		  m_tH460Features;
    
	tagCallParam()
	{
		Clear();	
		CreateConfId();
	}

	void Clear()
	{
		m_emConfGoalType = cmCreate;
		m_emCallType     = cmCallTypeP2P; 
		m_emEndpointType = emEndpointTypeUnknown;
		m_dwCallRate = 0;
		memset(m_atCallingAliasAddr,0,sizeof(m_atCallingAliasAddr));
		memset(m_atCalledAliasAddr,0,sizeof(m_atCalledAliasAddr));
		memset(&m_tCalledAddr, 0, sizeof(m_tCalledAddr));
		memset(&m_tCallingAddr, 0, sizeof(m_tCallingAddr));
		m_tCalledAddr.m_tNetAddr.m_wPort = CALLPORT;
		memset( m_abyConfId, 0, sizeof(m_abyConfId));		
		memset( m_abyCallId, 0, sizeof(m_abyCallId));
		memset( m_achDisplay,0, sizeof(m_achDisplay));
		memset( m_abyUserInfo,0,sizeof(m_abyUserInfo));
		m_nUUSize = 0;
		
		m_bIsEncrypt = FALSE;

		m_nProductIdSize = 0;
		m_nVerIdSize = 0;
        memset(m_abyProductId, 0, sizeof(m_abyProductId));
        memset(m_abyVersionId, 0, sizeof(m_abyVersionId));
		m_bySupportMediaTraversal = emNotSupportNATFWTraversal;
		memset( &m_tH460Features, 0, sizeof(m_tH460Features) );

		m_nNonStandLen = 0;
		memset( m_abyNonStandData, 0, LEN_NONSTANDARD_MAX );
	}

    //�����ն�����
    void SetEndpointType(emEndpointType emType)
    {
        m_emEndpointType = emType;
    }
    //�õ��ն�����
    emEndpointType GetEndpointType()
    {
        return m_emEndpointType;
    }
    

    //�����������
    void SetCallRate( u32 dwCallRate )
    {
        m_dwCallRate = dwCallRate;
    }
    //�õ��������
    u32 GetCallRate()
    {
        return m_dwCallRate;
    }
	//���ñ��е�ַ
	void SetCalledAddr(u32 dwIp,u16 wPort = CALLPORT)
	{
		TNETADDR addr;
		addr.SetNetAddress( dwIp, wPort==0 ? CALLPORT : wPort );
		addr.SetIPAddr_Type( TYPE_IPV4 );
		m_tCalledAddr.SetIPCallAddr( &addr );
	}

//add by yj for ipv6
	//���ñ��е�ַ(ipv6)
//	void SetCalledAddr_Ipv6(u8* dwIp_ipv6, s16 swScopeId,u16 wPort = CALLPORT)
	void SetCalledAddr_Ipv6(u8* dwIp_ipv6,u16 wPort = CALLPORT)
	{
		TNETADDR addr;
		addr.SetNetAddress_Ipv6( dwIp_ipv6, wPort==0 ? CALLPORT : wPort);
		addr.SetIPAddr_Type( TYPE_IPV6 );
		m_tCalledAddr.SetIPCallAddr( &addr );
	}
	//��ñ���IP(ipv6)
	u8* GetCalledIp_Ipv6()
	{
		return m_tCalledAddr.GetIPAddr_Ipv6(); 
	}
//	s16 GetCalledIp_Ipv6_ScopeId()
//	{
//		return m_tCalledAddr.GetIPAddr_Ipv6_ScopeId();
//	}
// TAliasAddr& GetCalledIp()
// {
//    return m_tCalledAddr;
// }
// TAliasAddr& GetCallingIp()
// {
// 	return m_tCallingAddr;
// }
//end
	//��ñ���IP
	u32 GetCalledIp()
	{
		return m_tCalledAddr.GetIPAddr(); 
	}	
	//��ñ��ж˿�
	u16 GetCalledPort() 
	{ 
		return m_tCalledAddr.GetIPPort(); 
	}

	//���ñ��е�ַ
	void SetCalledAddr(AliasType eType,const s8* sAlias)
	{
		TALIASADDR aliasAddr;
		aliasAddr.SetAliasAddr( eType, sAlias );
		m_tCalledAddr.SetIPCallAddr( &aliasAddr );
	}
    //�õ����е�ַ
    TAliasAddr& GetCalledAddr()
    {
        return m_tCalledAddr;
    }

	//�������е�ַ
	void SetCallingAddr( u32 dwIp,u16 wPort = 0 )
	{
		TNETADDR addr;
        //Jacky Wei Replace port 0 with default CALLPORT for Bug00144938(Intercommunication problem with HUAWEI EP)
		//addr.SetNetAddress( dwIp, wPort==CALLPORT? 0 : wPort);
        addr.SetNetAddress(dwIp, wPort == 0 ? CALLPORT : wPort);
		addr.SetIPAddr_Type( TYPE_IPV4 );
		m_tCallingAddr.SetIPCallAddr( &addr );
	}
	//�������IP
	u32 GetCallingIp()
	{
		return m_tCallingAddr.GetIPAddr();	
	}	
	//������ж˿�
	u16 GetCallingPort()
	{
		return m_tCallingAddr.GetIPPort();	
	}
    //�������е�ַ
    void SetCallingAddr(AliasType eType,const char* sAlias)
    {
        TALIASADDR aliasAddr;
        aliasAddr.SetAliasAddr( eType, sAlias );
        m_tCallingAddr.SetIPCallAddr( &aliasAddr );
    }

	//add by yj for ipv6
	//�������е�ַ(ipv6)
//	void SetCallingAddr_Ipv6( u8* dwIp_ipv6,s16 swScopeId,u16 wPort = 0 )
	void SetCallingAddr_Ipv6( u8* dwIp_ipv6,u16 wPort = 0 )
	{
		TNETADDR addr;
        //Jacky Wei Replace port 0 with default CALLPORT for Bug00144938(Intercommunication problem with HUAWEI EP)
        //addr.SetNetAddress_Ipv6( dwIp_ipv6, wPort == 0 ? CALLPORT : wPort);
		addr.SetNetAddress_Ipv6(dwIp_ipv6, wPort == 0 ? CALLPORT : wPort);
		addr.SetIPAddr_Type( TYPE_IPV6 );
		m_tCallingAddr.SetIPCallAddr( &addr );
	}
	//�������IP(ipv6)
	u8* GetCallingIp_Ipv6()
	{
		return m_tCallingAddr.GetIPAddr_Ipv6(); 
	}
//	s16 GetCallingIp_Ipv6_ScopeId()
//	{
//		return m_tCalledAddr.GetIPAddr_Ipv6_ScopeId();
//	}
	//end

    //�õ����е�ַ
    TAliasAddr& GetCallingAddr()
    {
        return m_tCallingAddr;
    }   

	//�������б�����ַ	��ΪԴ�˵���Ϣ
	void SetCallingAliasaddr( TAliasAddr &tAliasAddr, u8 addrNo )
	{
		if ( addrNo < type_others+1  )
		{
			m_atCallingAliasAddr[addrNo] = tAliasAddr;
		}
	}
	//��ȡ���б�����ַ
	PTAliasAddr GetCallingAliasaddr( u8 addrNo )
	{
		if ( addrNo < type_others+1  )
		{
			return &(m_atCallingAliasAddr[addrNo]);
		}
		return NULL;
	}
	
	//���ñ��б�����ַ	��ΪĿ�Ķ˵���Ϣ
	void SetCalledAliasAddr( TAliasAddr &tAliasAddr, u8 byAddrNo )
	{
		if ( byAddrNo < type_others+1  )
		{
			m_atCalledAliasAddr[byAddrNo] = tAliasAddr;
		}		
	}
	//��ȡ���б�����ַ
	PTAliasAddr GetCalledAliasAddr( u8 byAddrNo )
	{
		if ( byAddrNo < type_others+1  )
		{
			return &(m_atCalledAliasAddr[byAddrNo]);
		}
		return NULL;
	}

	//���û����
	void SetConfId(const u8* pchConfId,u8 byLen)
	{
		if( pchConfId == NULL || byLen <= 0 )
		{
			return;
		}

		s32 nReal = min(max(LEN_1, byLen), LEN_GUID);
		memcpy(m_abyConfId, pchConfId, nReal);
	}
	//����ų���
	s32 GetConfIdSize()
	{
		return LEN_GUID;
	};
	//��ȡ�����
	s32 GetConfId(u8* pbyConfId, s32 nLen)
	{
		if( pbyConfId == NULL || nLen <= 0 )
		{
			return 0;
		}

		s32 nReal = min(max(LEN_1, nLen), LEN_GUID);
		memcpy( pbyConfId, m_abyConfId, nReal );
		return nReal;
	}

	//����һ�������
	void CreateConfId()
	{
		memcpy(m_abyConfId, GetGUID(), LEN_GUID);
	}
	
	//����һ��Callidentifier
	void CreateCallId()
	{
		memcpy(m_abyCallId, GetGUID(), LEN_GUID);
	}
	//���ú���ID
	void SetCallId(const u8* pbyCallId, u8 byLen)
	{
		if( pbyCallId == NULL || byLen <= 0 )
		{
			return;
		}
		CreateCallId();
		s32 nReal = min(max(LEN_1, byLen), LEN_GUID);
		memcpy(m_abyCallId, pbyCallId, nReal);
	}
	//��ȡ����ID�ĳ���
	s32 GetCallIdSize()
	{
		return LEN_GUID;
	};
	//��ȡ����ID
	s32 GetCallId(u8* pbyCallId, s32 nLen)
	{
		if(pbyCallId == NULL|| nLen <= 0 )
		{
			return 0;
		}
		
		s32 nReal = min(max(LEN_1, nLen), LEN_GUID);
		memcpy(pbyCallId, m_abyCallId, nReal);
		return nReal;
	}

	//������ʾ��Ϣ
	void SetDisplayInfo(const s8* pchInfo)
	{
		if (pchInfo == NULL|| strlen(pchInfo) < LEN_DISPLAY_MIN)
		{
			return ;
		}
		strncpy( m_achDisplay, pchInfo, LEN_DISPLAY_MAX );
		m_achDisplay[LEN_DISPLAY_MAX] = 0;
	}
	//�����ʾ��Ϣ
	s8* GetDisplayInfo()
	{
		return m_achDisplay;
	}
	
	//����UserInfo
	void SetUserInfo(const u8* pchUserInfo, u8 byLen)
	{
		if(pchUserInfo == NULL || byLen < LEN_USERINFO_MIN)
		{
			return ;
		}
	    u8 length = min(LEN_USERINFO_MAX, byLen);
		memcpy(m_abyUserInfo,pchUserInfo,length);
		m_nUUSize = length;
	}	
	//���UserInfo����
	s32 GetUserInfoSize()
	{
		return m_nUUSize;
	}
	//��ȡUserInfo
	s32 GetUserInfo(u8* pbyUserInfo, u8 byLen)
	{
		if(pbyUserInfo == NULL || byLen < 1)
		{
			return 0;
		}
        s32 nReal = min(byLen, m_nUUSize);
		memcpy(pbyUserInfo, m_abyUserInfo, nReal);
		return nReal;
	}	
	//���ü���
	void SetIsEncrypt( BOOL bIsEncrypt )
	{
		m_bIsEncrypt = bIsEncrypt;
	}
	//�Ƿ����
	BOOL IsEncrypt()
	{
		return m_bIsEncrypt;
	}

	//��ָ�븳ֵ�����ܱ��棬 С�ģ���������������
	BOOL SetNonStandData(u8 *pBuf, s32 nLen)
	{
		if(nLen < 0 ||nLen > LEN_NONSTANDARD_MAX)
		{
			return  FALSE;
		}
		memcpy( m_abyNonStandData, pBuf, nLen );
		m_nNonStandLen = nLen;
	    return TRUE;
	}
    //��ȡָ�룬���ܱ���С�ģ���������������
	BOOL GetNonStandData(u8 **ppBuf, s32 *pnLen)
	{
		if(ppBuf == NULL|| pnLen == NULL)
		{
			return FALSE;
		}
		*ppBuf = m_abyNonStandData;
		*pnLen = m_nNonStandLen;
		return TRUE;
	}

	//���ò�Ʒ��
	void SetProductId(u8 *pbyId, s32 nLen)
	{
		if(pbyId == NULL|| nLen <= 0 )
		{
			return ;
		}
		memset( m_abyProductId, 0, sizeof(m_abyProductId) );
		s32 nReal = min(max(LEN_1, nLen), LEN_256);
		m_nProductIdSize = nReal;
        if(nLen >= LEN_1)
		{
			memcpy(m_abyProductId, pbyId, nReal);
		}
	}
	//��ȡ��Ʒ�ų���
	s32 GetProductIdSize()
	{
		return m_nProductIdSize;
	}
	//��ȡ��Ʒ��
	s32 GetProductId(u8 *pbyId, s32 nLen)
	{
		if( pbyId == NULL || nLen <= 0 || m_nProductIdSize <= 0 )
		{
			return 0;
		}
		s32 nReal = min(nLen, m_nProductIdSize); 
		memcpy(pbyId, m_abyProductId, nReal);
		return nReal;
	}
	//���ð汾��	
	void SetVersionId(u8 *pbyId, s32 nLen)
	{
		if(pbyId == NULL|| nLen <= 0 )
		{
			return ;
		}
		memset( m_abyVersionId, 0, sizeof(m_abyVersionId) );
		s32 nReal = min(max(LEN_1, nLen), LEN_256);
		m_nVerIdSize = nReal;
        if(nLen >= LEN_1)
		{
			memcpy(m_abyVersionId, pbyId, nReal);
		}
	}
	//��ȡ�汾�ų���
	s32 GetVersionIdSize()
	{
		return m_nVerIdSize;
	}
	//��ȡ�汾��
	s32 GetVersionId(u8 *pbyId, s32 nLen)
	{
		if( pbyId == NULL || nLen <= 0 || m_nVerIdSize <= 0 )
		{
			return 0;
		}
		s32 nReal = min(nLen, m_nVerIdSize); 
		memcpy(pbyId, m_abyVersionId, nReal);
		return nReal;
	}

	void SetSupportMediaTraversal(emNATFWTraversal emNet)
	{
		m_bySupportMediaTraversal = emNet;
	}
	emNATFWTraversal GetSupportMediaTraversal()
	{
		return m_bySupportMediaTraversal;
	}
	void SetH460features( const TH460Features &th460features )
	{
		memcpy( &m_tH460Features, &th460features, sizeof(TH460Features) );
	}
	void GetH460features( TH460Features &th460features )
	{
		memcpy( &th460features, &m_tH460Features, sizeof(TH460Features) );
	}

}TCALLPARAM,*PTCALLPARAM;


//�����б�
typedef struct tagConferences
{
	u8		   m_byNum;
	TCONFINFO  m_atConfInfo[MAX_CONF_NUM];
	
	tagConferences():m_byNum(0){}
	
	void Clear()
	{
		m_byNum = 0;
		memset( m_atConfInfo, 0, sizeof(m_atConfInfo) );
	}
	
	//���û�����Ŀ
	void SetConfNum( u8 num)
	{
		m_byNum = num;
	}
	//��ȡ������Ŀ
	u8 GetConfNum()
	{
		return m_byNum;
	}

	//���û�����Ϣ
	void SetConfInfo( TCONFINFO &tConfInfo, u8 byConfNo )
	{
		if ( byConfNo >= MAX_CONF_NUM ) 
			return ;		
		m_atConfInfo[byConfNo] = tConfInfo;
	}
	//��ȡ������Ϣ
	PTCONFINFO GetConfInfo( u8 byConfNo )
	{
		if ( byConfNo >= MAX_CONF_NUM ) 
			return  NULL;
		return &(m_atConfInfo[byConfNo]);
	}
}TCONFERENCES,*PTCONFERENCES;

//begin with added by wangxiaoyi for facility with non-strandard conflist message on 5 August 2010
typedef struct tagFacilityConfList_NSM
{
protected:
	u8   m_abyConfId[LEN_GUID+1];	//����ID
	u16  m_wListIdx;				// ��TCONFERENCES�ṹ�еĴ��λ��������������

	//�����Ǳ�����
	s8	 m_sConfE164[LEN_ALIAS+1];	// ����E164����
	u8	 m_byMtNum;					// ����ն���
	u16  m_wRemainTime;				// ����ʣ��ʱ��, ��λ�Ƿ���
	u32  m_dwReserved1;
	u32  m_dwIsContinue;
	BOOL32         m_bConfListNonStandard;// whether contains non-standard information or not when facilityreason is conferenceListChoice

	////////
public:
	tagFacilityConfList_NSM()
	{
		Clear();
	}
	
	void Clear()
	{
		memset(m_abyConfId,0,sizeof(m_abyConfId));
		SetListIdx(0);
		SetConfE164( NULL, 0 );
		SetMtNum( 0 );
		SetRemainTime( 0 );
		SetConfListNonStandard( FALSE );
	}
	//���û���ID
	void SetConfId( u8 *pbyConfId, u32 dwLen )
	{
		if ( pbyConfId == NULL )
			return;
		
		u32 realLen = min(dwLen, LEN_GUID);
		memcpy( m_abyConfId, pbyConfId, realLen );
		m_abyConfId[realLen] = '\0';
	}
	//��ȡ����ID
	u8* GetConfId()
	{
		return m_abyConfId;
	}
	//���ô��λ������
	void SetListIdx( u16 wListIdx )
	{
		m_wListIdx = htons(wListIdx);
	}
	//��ȡ���λ������
	u16 GetListIdx()
	{
		return ntohs(m_wListIdx);
	}
	// ���û���E164����
	void SetConfE164( s8 * psConfE164, u8 byLen )
	{
		memset( m_sConfE164, 0, sizeof(m_sConfE164) );
		if ( NULL == psConfE164 || 0 == byLen )
		{
			return;
		}
		u8 byRealLen = (u8)min( byLen, LEN_ALIAS );
		memcpy( m_sConfE164, psConfE164, byRealLen );
		return;
	}
	// ��ȡ����E164����
	s8 * GetConfE164( void )
	{
		return m_sConfE164;
	}
	// ��������ն���
	void SetMtNum( u8 byMtNum )
	{
		m_byMtNum = byMtNum;
	}
	// ��ȡ����ն���
	u8   GetMtNum( void )
	{
		return m_byMtNum;
	}
	// ���û���ʣ��ʱ��
	void SetRemainTime( u16 wRemainTime )
	{
		m_wRemainTime = htons(wRemainTime);
	}
	// ��ȡ����ʣ��ʱ��
	u16  GetRemainTime( void )
	{
		return ntohs(m_wRemainTime);
	}
	BOOL32 IsIdleConf(void)
	{
		return ( GetMtNum() == 0 ) ? TRUE : FALSE;
	}

    void SetContinueFlag( BOOL32 bIsContinue )
    {
        m_dwIsContinue = bIsContinue ? htonl(1) : htonl(0);
    }
    BOOL32 IsContinue( void )
    {
        return ( ntohl(m_dwIsContinue) == 1 ) ? TRUE : FALSE;
    }
	void SetConfListNonStandard( BOOL32 bConfListNonStandard )
	{
		m_bConfListNonStandard = htonl(bConfListNonStandard);
	}
	BOOL32 IsConfListNonStandard()
	{
		return ntohl(m_bConfListNonStandard);
	}
	void SetReserved1( u32 dwReserved )
	{
		m_dwReserved1 = htonl( dwReserved );
	}
	u32 GetReserved1( void )
	{
		return ntohl( m_dwReserved1 );
	} 
}
TFacilityConfList_NSM,*PTFaclilityConfList_NSM;
//end with added by wangxiaoyi for facility with non-strandard conflist message on 5 August 2010
//Facility����
typedef struct tagFacilityUUIE
{
	u8			  m_byReason;					//FacilityReason
	TAliasAddr	  m_tAlternativeAddrAlias;
	TCONFERENCES  m_tConferences;

	u8			  m_abyCallId[LEN_GUID]; 
	BOOL          m_bExistCallId;
	
	//begin with added by wangxiaoyi for facility with non-strandard conflist message on 5 August 2010

	TFacilityConfList_NSM  m_atConfList_NSM[MAX_CONF_NUM];

	//end with added by wangxiaoyi for facility with non-strandard conflist message on 5 August 2010

	tagFacilityUUIE()
	{
		Clear();
	}

	void Clear()
	{
		m_byReason = unknown;
		m_tAlternativeAddrAlias.Clear();
		m_tConferences.Clear();
		m_bExistCallId = FALSE;
		memset(m_atConfList_NSM,0,MAX_CONF_NUM * sizeof(TFacilityConfList_NSM));
	}

	//����TAliasAddr
	void SetAliasAddr( TAliasAddr &tAliasAddr )
	{
		m_tAlternativeAddrAlias = tAliasAddr;
	}
	//��ȡTAliasAddr
	TAliasAddr& GetAliasAddr()
	{
		return m_tAlternativeAddrAlias;
	}

	//����TCONFERENCES
	void SetConferences( TCONFERENCES &tConf )
	{
		m_tConferences = tConf;
	}
	//��ȡTCONFERENCES
	TCONFERENCES& GetConferences()
	{
		return m_tConferences;
	}

	//��ȡ����ID
	s32 GetCallId(u8* pbyCallId, s32 nLen)
	{
		if(pbyCallId == NULL|| nLen <= 0 )
		{
			return 0;
		}
		
		s32 nReal = min(max(LEN_1, nLen), LEN_GUID);
		memcpy(pbyCallId, m_abyCallId, nReal);
		return nReal;
	}
	
	//���ú���ID
	void SetCallId(const u8* pbyCallId,u8 byLen)
	{
		if( pbyCallId == NULL || byLen <= 0 )
		{
			return;
		}
		m_bExistCallId = TRUE;
		
		s32 nReal = min(max(LEN_1, byLen), LEN_GUID);
		memcpy(m_abyCallId, pbyCallId, nReal);
	}

    void SetContinueFlag( BOOL32 bIsContinue )
    {
        m_atConfList_NSM[MAX_CONF_NUM-1].SetContinueFlag( bIsContinue );
    }
    BOOL32 IsContinue( void )
    {
        return m_atConfList_NSM[MAX_CONF_NUM-1].IsContinue();
    }

}TFACILITYINFO,*PTFACILITYINFO;

//����ͬ���ṹ  
typedef struct tagEncryptSync
{
	s32			  m_nSynchFlag;			         //shall be the Dynamic PayloadType for H.323
	u8			  m_abyH235Key[LEN_H235KEY_MAX]; //H.235 encoded value(1-65535)
	s32           m_nH235KeyLen;

    tagEncryptSync()
	{
		Reset();
	}

    void Reset()
	{
		m_nSynchFlag  = 0;
		m_nH235KeyLen = 0;
	}

    void host2net(BOOL bhton)
    {
        if (bhton)
        {
            m_nSynchFlag  = htonl(m_nSynchFlag);
            m_nH235KeyLen = htonl(m_nH235KeyLen);
        }
        else
        {
            m_nSynchFlag  = ntohl(m_nSynchFlag);
            m_nH235KeyLen = ntohl(m_nH235KeyLen);
        }
    }
    
    //����SynchFlag
	void SetSynchFlag(s32 nFlag)
	{ 
		m_nSynchFlag = nFlag; 
	}
    //��ȡSynchFlag
	s32  GetSynchFlag() 
	{
		return m_nSynchFlag; 
	}

    //����H235Key
	s32 SetH235Key(u8 *pBuf, s32 nLen)
	{
		m_nH235KeyLen = min(max(0, nLen), LEN_H235KEY_MAX);
		memcpy(m_abyH235Key, pBuf, m_nH235KeyLen);
		return m_nH235KeyLen;
	}	
    //��ȡH235Key�ĳ���
	s32 GetH235KeyLen() 
	{
		return m_nH235KeyLen; 
	}
    //��ȡH235Key
	u8* GetH235Key()
	{
		return m_abyH235Key;
	}
}TEncryptSync;

//���ŵ�����
typedef struct tagChannelParam 
{
	TNETADDR	  m_tRtp;				//rtp��ַ ,incoming chanʹ��
	TNETADDR	  m_tRtcp;				//rtcp��ַ,incoming and outgoing chanʹ��
	u16			  m_wPayloadType;		//ý��ͨ������	

	TVideoCap	  m_tVideoCap;
	TAudioCap	  m_tAudioCap;
	TDataCap	  m_tDataCap;
	TG7231Cap	  m_tG7231Cap;

	BOOL		  m_bFlowToZero;		//�Ƿ�Ҫ���Ͷ����ŵ�����ʱ����������
	TTERLABEL	  m_tSrcTer;
	TTERLABEL	  m_tDstTer;

	u8			  m_byDynamicPT;		//��̬�غ�����ֵ(96~127)
	emEncryptType m_emEncryptType;		//��������
	TEncryptSync  m_tEncryptSync;       //master�����ô˽ṹ         

    //for H239
    BOOL          m_bIsH239DStream;     //�ڴ���Ƶͨ��ʱָ���Ƿ�H239Э���˫��

    //for RSVP
    BOOL          m_bSupportRSVP;       //�Ƿ�֧��RSVP��˫����֧��RSVP����ΪTRUE
    
    // guzh [9/28/2007] 
    u8            m_byFECType;          //ǰ��������͡�����Ƶͨ������

    // guzh [11/28/2007] 
    TH264VideoCap m_tH264Cap;           //H.264������Ƶ��������m_tVideoCap���⣬ֻ����дһ������
    // guzh [2008/06/06]
    TAACCap       m_tAacCap;            //AAC LC/LD ��Ƶ����
	
	emH264NALMode m_emH264NALMode;
	
		TNETADDR	  m_tKeepAliveAddr;		//460 server's rtp sending address for keep-alive channel added by wangxiaoyi 29 July 2010
	u16			  m_byKeepAlivePayload;	//�򶴰��غ�����(0~127)
	u32			  m_dwKeepAliveInterval; //�򶴰�����ʱ����

    void host2net(BOOL bhton)
    {
        m_tRtp.host2net(bhton);
        m_tRtcp.host2net(bhton);
		m_tKeepAliveAddr.host2net(bhton);//added by wangxiaoyi for h460 keepalivechannel
        m_wPayloadType = htons(m_wPayloadType);
        m_tVideoCap.host2net(bhton);
        m_tH264Cap.host2net(bhton);
        m_tAudioCap.host2net(bhton);
        m_tDataCap.host2net(bhton);
        m_tG7231Cap.host2net(bhton);
        m_tAacCap.host2net(bhton);
        m_bFlowToZero = htonl(m_bFlowToZero);
        // m_tSrcTer 
        // m_tDstTer
        // m_byDynamicPT
        m_emEncryptType = (emEncryptType)htonl(m_emEncryptType);
        m_tEncryptSync.host2net(bhton);
        m_bIsH239DStream = htonl(m_bIsH239DStream);
        m_bSupportRSVP = htonl(m_bSupportRSVP);

        // m_byFECType

		m_emH264NALMode  = (emH264NALMode)htonl((u32)m_emH264NALMode);

		m_byKeepAlivePayload = htons(m_byKeepAlivePayload);
		m_dwKeepAliveInterval = htonl(m_dwKeepAliveInterval);
    }

public:
	tagChannelParam()
	{
		Reset();
	};

	void Reset()
	{
		m_tRtp.Clear();
		m_tRtcp.Clear();
		m_tKeepAliveAddr.Clear();//added by wangxiaoyi for h460 keepalivechannel
		m_tSrcTer.Clear();
		m_tDstTer.Clear();
        m_wPayloadType = emPayloadTypeBegin;
		m_byDynamicPT   = 0;  
		m_bFlowToZero   = FALSE; 
		m_emEncryptType = emEncryptTypeNone;
		m_tEncryptSync.Reset();

        m_bIsH239DStream  = FALSE;
        m_bSupportRSVP    = FALSE;
    
        SetFECType(emFECNone);     
		m_emH264NALMode = emNALNode;

		m_byKeepAlivePayload = 0;
		m_dwKeepAliveInterval = 0;
	}

    //�����Ƿ�֧��RSVP
    void SetSupportRSVP(BOOL bSupportRSVP) 
    {	
        m_bSupportRSVP = bSupportRSVP; 
    }
    BOOL IsSupportRSVP() 
    {
        return m_bSupportRSVP;
    }

    //����FEC����
    void SetFECType(u8 emType)
    {
        m_byFECType = emType;
    }
    u8 GetFECType() const
    {
        return m_byFECType;
    }
	
    //����RTP����
	void SetRtp(TNETADDR& rtp) 
	{ 
		m_tRtp = rtp; 
	}
    //�õ�RTP����
	TNETADDR& GetRtp() 
	{
		return m_tRtp; 
	};
	//����KeepAliveAddr����added by wangxiaoyi for h460 keepalivechannel
	void SetKeepAliveAddr(TNETADDR& keepaliveaddr) 
	{ 
		m_tKeepAliveAddr = keepaliveaddr; 
	}
    //�õ�KeepAliveAddr����added by wangxiaoyi for h460 keepalivechannel
	TNETADDR& GetKeepAliveAddr() 
	{
		return m_tKeepAliveAddr; 
	};

    //����RTCP����
	void SetRtcp(TNETADDR& rtcp) 
	{
		m_tRtcp = rtcp; 
	}
    //�õ�RTCP����
	TNETADDR& GetRtcp() 
	{
		return m_tRtcp; 
	}

    //����FlowToZero
	void SetIsFlowToZero(BOOL bFlowToZero) 
	{	
		m_bFlowToZero = bFlowToZero; 
	}
	BOOL IsFlowToZero() 
	{
		return m_bFlowToZero;
	}
	
    //���ü�������
    void SetEncryptType(emEncryptType emType)
	{
		m_emEncryptType = emType; 
	}
    //�õ���������
	emEncryptType GetEncryptType()
	{
		return m_emEncryptType;
	}

    //����Դ��TTERLABEL
	void SetSrcTerLabel( TTERLABEL& tTer) 
	{ 
		m_tSrcTer = tTer;
	}
    //�õ�Դ��TTERLABEL
    TTERLABEL& GetSrcTerLabel() 
	{ 
		return m_tSrcTer; 
	}

    //����Ŀ�Ķ�TTERLABEL
	void SetDstTerLabel( TTERLABEL& tTer) 
	{ 
		m_tDstTer = tTer;
	}
    //�õ�Ŀ�Ķ�TTERLABEL
    TTERLABEL& GetDstTerLabel() 
	{ 
		return m_tDstTer; 
	}

    //���ö�̬�غ�����
	BOOL SetDynamicPayloadParam( u8 byDynamicPT )
	{
		if ( byDynamicPT>=96 && byDynamicPT<=127 ) 
		{
			m_byDynamicPT = byDynamicPT;
			return TRUE;
		}
		return FALSE;
	}
	u8 GetDynamicPayloadParam()
	{
	    return m_byDynamicPT;
	} 
    //�Ƿ�̬�غ����� 
    BOOL IsDynamicPayload()	
    { 
        return (m_byDynamicPT >= 96)&&(m_byDynamicPT <= 127); 
    }

    //�õ��غ�����
    u16 GetPayloadType()
    {
        return m_wPayloadType; 
    }

    //������Ƶ������������H.264
	BOOL SetPayloadParam(u16 wPayloadType, TVideoCap &tVideoCap)
	{
		if ( !PayloardIsVideoType(wPayloadType) || wPayloadType == v_h264 )
		{
            // guzh [11/28/2007] critical error!
            OspPrintf(1, 0, "[H323Adp][TCHANPARAM::SetPayloadParam] Payload param(%d) error! TVideoCap\n", wPayloadType);
			return FALSE;
		}
		m_tVideoCap = tVideoCap;
		m_wPayloadType = wPayloadType;
		return TRUE;
	}
    //�õ���Ƶ����
    BOOL GetPayloadParam(u16 wPayloadType, TVideoCap *ptVideoCap)
    {
        if( !PayloardIsVideoType(wPayloadType) || wPayloadType == v_h264 || ptVideoCap == NULL )
        {
            // guzh [11/28/2007] critical error!
            OspPrintf(1, 0, "[H323Adp][TCHANPARAM::GetPayloadParam] Payload param(%d) error! TVideoCap\n", wPayloadType);
            return FALSE;
        }
        *ptVideoCap = m_tVideoCap;
        return TRUE;
    }
    //����H.264��Ƶ����
    BOOL SetPayloadParam(u16 wPayloadType, TH264VideoCap &tVideoCap)
    {
        if ( wPayloadType != v_h264 )
        {
			OspPrintf(1, 0, "[H323Adp][TCHANPARAM::SetPayloadParam] Payload param(%d) error! TH264VideoCap\n", wPayloadType);
			return FALSE;
        }
        m_tH264Cap = tVideoCap;
        m_wPayloadType = wPayloadType;
        return TRUE;
    }
    //�õ�H.264��Ƶ����
    BOOL GetPayloadParam(u16 wPayloadType, TH264VideoCap *ptVideoCap)
    {        
        if( wPayloadType != v_h264 || ptVideoCap == NULL )
        {
			OspPrintf(1, 0, "[H323Adp][TCHANPARAM::GetPayloadParam] Payload param(%d) error! TH264VideoCap\n", wPayloadType);
            return FALSE;
        }
        *ptVideoCap = m_tH264Cap;
        return TRUE;
    }

    //������Ƶ������������G7231
	BOOL SetPayloadParam(u16 wPayloadType, TAudioCap &tAudioCap)
	{
		if ( !PayloardIsAudioType(wPayloadType) || 
             wPayloadType == a_g7231 ||
             wPayloadType == a_mpegaaclc || 
             wPayloadType == a_mpegaacld )
		{
            OspPrintf(1, 0, "[H323Adp][TCHANPARAM::SetPayloadParam] Payload param(%d) error! TAudioCap\n", wPayloadType);
			return FALSE;
		}
		m_tAudioCap = tAudioCap;
		m_wPayloadType = wPayloadType;
		return TRUE;
	}
    //�õ���Ƶ������������G7231/AAC
    BOOL GetPayloadParam(u16 wPayloadType, TAudioCap *ptAudioCap)
    {
        if (!PayloardIsAudioType(wPayloadType) || 
            wPayloadType == a_g7231 || 
            wPayloadType == a_mpegaaclc || 
            wPayloadType == a_mpegaacld || 
            ptAudioCap == NULL) 
        {
            OspPrintf(1, 0, "[H323Adp][TCHANPARAM::GetPayloadParam] Payload param(%d) error! TAudioCap\n", wPayloadType);
            return FALSE;
        }
        *ptAudioCap = m_tAudioCap;
        return TRUE;
    }

    //����G7231����
    BOOL SetPayloadParam(u16 wPayloadType, TG7231Cap &tG7231Cap)
    {
        if(wPayloadType != a_g7231)
        {
			OspPrintf(1, 0, "[H323Adp][TCHANPARAM::SetPayloadParam] Payload param(%d) error! TG7231Cap\n", wPayloadType);
            return FALSE;
        }
        m_tG7231Cap = tG7231Cap;
        m_wPayloadType = wPayloadType;
        return TRUE;
    }
    //�õ�G7231����
    BOOL GetPayloadParam(u16 wPayloadType, TG7231Cap *ptG7231Cap)
    {
        if(wPayloadType  != a_g7231|| ptG7231Cap == NULL )
        {
			OspPrintf(1, 0, "[H323Adp][TCHANPARAM::GetPayloadParam] Payload param(%d) error! TG7231Cap\n", wPayloadType);
            return FALSE;
        }
        *ptG7231Cap = m_tG7231Cap;
        return TRUE;
    }
    //����AAC����
    BOOL SetPayloadParam(u16 wPayloadType, TAACCap &tAacCap)
    {
        if (wPayloadType != a_mpegaaclc && wPayloadType  != a_mpegaacld)
        {
			OspPrintf(1, 0, "[H323Adp][TCHANPARAM::SetPayloadParam] Payload param(%d) error! TAACCap\n", wPayloadType);
            return FALSE;
        }
        m_tAacCap = tAacCap;
        m_wPayloadType = wPayloadType;
        return TRUE;
    }
    //�õ�AAC����
    BOOL GetPayloadParam(u16 wPayloadType, TAACCap *ptAacCap)
    {
        if((wPayloadType != a_mpegaaclc && wPayloadType  != a_mpegaacld) || ptAacCap == NULL )
        {
			OspPrintf(1, 0, "[H323Adp][TCHANPARAM::GetPayloadParam] Payload param(%d) error! TAACCap\n", wPayloadType);
            return FALSE;
        }
        *ptAacCap = m_tAacCap;
        return TRUE;
    }

    //�������ݲ���
	BOOL SetPayloadParam(u16 wPayloadType, TDataCap &tDataCap)
	{
		if (!PayloardIsDataType(wPayloadType))
		{
			OspPrintf(1, 0, "[H323Adp][TCHANPARAM::SetPayloadParam] Payload param(%d) error! TDataCap\n", wPayloadType);
            return FALSE;
		}
		m_tDataCap = tDataCap;
		m_wPayloadType = wPayloadType;
		return TRUE;
	}
    //�õ����ݲ���
    BOOL GetPayloadParam(u16 wPayloadType, TDataCap *ptDataCap)
    {
        if(!PayloardIsDataType(wPayloadType) || ptDataCap == NULL)
        {
			OspPrintf(1, 0, "[H323Adp][TCHANPARAM::GetPayloadParam] Payload param(%d) error! TDataCap\n", wPayloadType);
            return FALSE;
        }
        *ptDataCap = m_tDataCap;
        return TRUE;
    }

    //���ü���ͬ����Ϣ
	void SetEncryptSync( TEncryptSync &tSync)
	{ 
		m_tEncryptSync = tSync; 
	}
    //�õ�����ͬ����Ϣ
	TEncryptSync &GetEncryptSync() 
	{ 
		return m_tEncryptSync; 
	} 

	void SetH264NALMode(emH264NALMode emNALMode)
	{
		m_emH264NALMode = emNALMode;
	}
	
	emH264NALMode GetH264NALMode()
	{
		return m_emH264NALMode;
	}

	void SetKeepAlivePayload(u16 payload)
	{
		m_byKeepAlivePayload = payload;
	}
	u16 GetKeepAlivePayload()
	{
		return m_byKeepAlivePayload;
	}

	void SetKeepAliveInterval(u32 time)
	{
		m_dwKeepAliveInterval = time;
	}
	u32 GetKeepAliveInterval()
	{
		return m_dwKeepAliveInterval;
	}
	
}TCHANPARAM,*PTCHANPARAM;

typedef struct tagKeepAliveInfo
{
	TNETADDR	m_tKeepAliveNet;
	u16			m_wKeepAlivePayload;
	u32			m_dwKeepAliveInterval;

	tagKeepAliveInfo()
	{
		Clear();
	}
	void Clear()
	{
		m_tKeepAliveNet.Clear();
		m_wKeepAlivePayload = 0;
		m_dwKeepAliveInterval = 0;
	}
}TKeepAliveInfo, *PTKeepAliveInfo;
//�ն���Ϣ����
typedef struct tagTerminalInformation 
{
	TTERLABEL	m_tTerLabel;
	s8			m_achTerID[LEN_TERID + 1];

	tagTerminalInformation()
	{
		Clear();
	}

	void Clear()
	{
		m_tTerLabel.Clear();
        memset( m_achTerID, 0, sizeof(m_achTerID) );        
	}	
	
	//�����ն˱��
	void SetLabel(const PTTERLABEL ptLabel)
	{
		if (ptLabel != NULL)
		{
			memcpy( &m_tTerLabel, ptLabel, sizeof(m_tTerLabel) );
		}		
	}
	void SetLabel(u8 byMcuNo, u8 byTerNo)
	{
		if (byMcuNo < 193 && byTerNo <193)
		{
			m_tTerLabel.SetTerminalLabel(byMcuNo, byTerNo);
		}
	}
	//����ն˱��
	TTERLABEL& GetTerlabel()
	{
		return m_tTerLabel;
	}
	void GetLabel(u8& byMcuNo, u8& byTerNo)
	{
		m_tTerLabel.GetTerminalLabel( &byMcuNo, &byTerNo );
	}
	//���Mcu��
	u8 GetMcuNo() 
	{ 
		return m_tTerLabel.GetMcuNo();	
	}
	//����ն˺�
	u8 GetTerNo() 
	{ 
		return m_tTerLabel.GetTerNo();	
	}

	//�����ն�����
	BOOL SetName(const s8* pchName)
	{
		if (pchName != NULL)
		{
			strncpy( m_achTerID, pchName, LEN_TERID + 1 );
			m_achTerID[LEN_TERID] = '\0';
			return TRUE;
		}
		return FALSE;
	}
	//����ն�����
	s8* GetName()
	{
		return m_achTerID;
	}

	void operator = (tagTerminalInformation& tTerInfo)
	{
		m_tTerLabel.SetTerminalLabel( tTerInfo.m_tTerLabel.GetMcuNo(), 
									  tTerInfo.m_tTerLabel.GetTerNo() );

		strncpy( m_achTerID,tTerInfo.GetName(), LEN_TERID + 1);
	}

	bool operator != (tagTerminalInformation& tTerInfo)
	{
		if ( m_tTerLabel.GetMcuNo() == tTerInfo.m_tTerLabel.GetMcuNo() && 
			 m_tTerLabel.GetTerNo() == tTerInfo.m_tTerLabel.GetTerNo() &&
			 strcmp( m_achTerID, tTerInfo.m_achTerID ) == 0 )
		{
			return false;
		}
		return true;
	}

	bool operator == (tagTerminalInformation& tTerInfo)
	{
		if ( m_tTerLabel.GetMcuNo() == tTerInfo.m_tTerLabel.GetMcuNo() && 
			 m_tTerLabel.GetTerNo() == tTerInfo.m_tTerLabel.GetTerNo() &&
			 strcmp( m_achTerID, tTerInfo.m_achTerID ) == 0 )
		{
			return true;
		}
		return false;
	}
}TTERINFO,*PTTERINFO;

//ͨѶģʽ����
typedef struct tagCommunicationModeCommandInfo
{
	u8				m_bySessionID;
	u8				m_byAssociatedSessionID;
	TTERLABEL		m_tTerLabel;							//���Ϊ<255,255>��ʾ�����ն�
	u8				m_byDataType;							//type_audio/type_video/type_data
	u16				m_wPayloadType;							//ý��������
	TNETADDR		m_tRtp;									//rtp��ַ		
	TNETADDR		m_tRtcp;								//rtcp��ַ
	TTERLABEL		m_tDestination;							//Ŀ���ն�,<0,0>��ʾ��Ч
	u8				m_bySessionDescriptLen;
	s8				m_achSessionDescript[MAXSessionDescript+1];
					
	tagCommunicationModeCommandInfo()
	{
		Clear();
	}
	
	void Clear()
	{
		m_bySessionID = 0;
		m_byAssociatedSessionID = 0;
		m_tTerLabel.Clear();
		m_byDataType = 0;
		m_wPayloadType = 0;
		m_tRtp.Clear();
		m_tRtcp.Clear();
		m_tDestination.Clear();
		m_bySessionDescriptLen = 0;
		memset( m_achSessionDescript, 0, sizeof(m_achSessionDescript) );
	}

    //����SessionID
	void SetSessionID( u8 bySessionID)
	{
		m_bySessionID = bySessionID;
	}
    //�õ�SessionID
	u8 GetSessionID()
	{
		return m_bySessionID;
	}

    //����AssociatedSessionID
	void SetAssociatedSessionID( u8 byAssociatedSessionID )
	{
		m_byAssociatedSessionID = byAssociatedSessionID;
	}
    //�õ�AssociatedSessionID
	u8 GetAssociatedSessionID()
	{
		return m_byAssociatedSessionID;
	}

    //����TTERLABEL
	void SetTerLabel( TTERLABEL &tTerLabel)
	{
		m_tTerLabel = tTerLabel;
	}
    //�õ�TTERLABEL
	TTERLABEL& GetTerLabel()
	{
		return m_tTerLabel;
	}

    //������������
	void SetDataType( u8 byDataType)
	{
		m_byDataType = byDataType;
	}
    //�õ���������
	u8 GetDataType()
	{
		return m_byDataType;
	}

    //����ý������
	void SetPayloadType( u16 wPayloadType)
	{
		m_wPayloadType = wPayloadType;
	}
    //�õ�ý������
	u16 GetPayloadType()
	{
		return m_wPayloadType;
	}

    //����RTP��ַ
	void SetRTPAddr( TNETADDR &tRtp )
	{
		m_tRtp = tRtp;
	}
    //�õ�RTP��ַ
	TNETADDR& GetRTPAddr()
	{
		return m_tRtp;
	}

    //����RTCP��ַ
	void SetRTCPAddr( TNETADDR &tRtcp )
	{
		m_tRtcp = tRtcp;
	}
    //�õ�RTCP��ַ
	TNETADDR& GetRTCPAddr()
	{
		return m_tRtcp;
	}

    //����Ŀ�Ķ�TTERLABEL
	void SetDestTerLabel( TTERLABEL &tTerLabel)
	{
		m_tDestination = tTerLabel;
	}
    //�õ�Ŀ�Ķ�TTERLABEL
	TTERLABEL& GetDestTerLabel()
	{
		return m_tDestination;
	} 
	
    //����SessionDescript
	void SetSessionDescript( s8 *pSessionDescript, u8 byLen )
	{
		m_bySessionDescriptLen = min( byLen, MAXSessionDescript );
		strncpy( m_achSessionDescript, pSessionDescript, m_bySessionDescriptLen );
		m_achSessionDescript[m_bySessionDescriptLen] = '\0';
	}
    //�õ�SessionDescript
	s8* GetSessionDescript()
	{
		return m_achSessionDescript;
	}
    //�õ�SessionDescript����
	u16 GetSessionDescriptLen()
	{
		return m_bySessionDescriptLen;
	}
}TCOMMODEINFO,*PTCOMMODEINFO;

u16 GetEType( IN u16 wType, IN u8 byEBits);
u16 GetH239Type( IN u16 wType );
BOOL IsH239Type( IN u16 wType );
/************************************
* �������ṹ
* Ŀǰ����Ƶ֧��:h261,h263,h264,mpeg4,h263+,h262
* Ŀǰ����Ƶ֧��:G711u(64k),G711a(64k),G722(64k),G7231,G728,G729,G7221C,MP3,MP2AAC,MP4AAC.
* 
* guzh [12/17/2007] �����ṹ
* guzh [04/03/2008] �����ṹ
 *************************************/
typedef struct tagCapSet
{
private:
	u16 m_awCapTable[MAX_CAPTABLE_SIZE]; //PayloadType array
	u16 m_aaawCapDesc[MAX_DESCAP_NUM][MAX_SIMUCAP_NUM][MAX_ALTCAP_NUM]; //PayloadType array
    //Video
	TVideoCap       m_tH261Cap;
	TVideoCap       m_tH263Cap;
	TVideoCap       m_tH263plusCap;
	TVideoCap       m_tMpeg4Cap;
    TVideoCap       m_tH262Cap;
    //Audio
	TAudioCap       m_tG711u;   
	TAudioCap       m_tG711a;   
	TAudioCap       m_tG722;    
	TAudioCap       m_tG728;	   
	TAudioCap       m_tG729;
	TAudioCap       m_tMP3;
    TAudioCap       m_tG7221c;
    TAACCap         m_tMpegAacLc;
    TAACCap         m_tMpegAacLd;		
	TG7231Cap       m_tG7231;
    //Data
	TDataCap        m_tT120;
	TDataCap        m_tH224;

    /*�غ����͵��ڲ�ת��:
    |<--------------���ܺ�H239���غ�ת��---------- >|<���ֽ�Ϊ�ϲ�ʹ�õ�����>|
    ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    +  0  +  0  +  0  +  0  +  1  +  1  +  1  +  1  +  payloadType           +             
    ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            + H239+ AES + DES +NoEnc+   
    */
	u8              m_byEncryptBits;	        //enum emEncryptType
    BOOL            m_bIsSupportH239;         //֧��H.239������
    BOOL            m_bSupportRSVP;           //�Ƿ�֧��RSVP����
	BOOL            m_bSupportActiveH263Plus; //�Ƿ�֧��H.263+
    u8              m_byFECBits;              //ǰ�����

    //guzh [2008/04/03] H.264 ����
    TH264VideoCap   m_atH264Cap[MAX_H264CAP_NUM];
	u8              m_awH264ToSubId[MAX_CAPTABLE_SIZE]; //H264 payload id �� sub id ӳ���
	u8              m_bySubId;
	emH264NALMode   m_emH264NALMode;

	TAudioCap       m_tG719;   //ruiyigen 20091012 Add At Rear
	
public:
	tagCapSet()
	{
		Clear();
	}

	void Clear()
	{
		memset( m_awCapTable, 0, sizeof(m_awCapTable) ); 
		memset( m_aaawCapDesc, 0xFF, sizeof(m_aaawCapDesc) ); 
		memset(m_awH264ToSubId, 0xFF, sizeof(m_awH264ToSubId));

		m_tH261Cap.Clear();
		m_tH263Cap.Clear();
		m_tH263plusCap.Clear();
		for (u8 byLoop = 0; byLoop < MAX_H264CAP_NUM; byLoop++)
        {
            m_atH264Cap[byLoop].Clear();
        }
		m_tMpeg4Cap.Clear();
        m_tH262Cap.Clear();
	
		m_tG711u.Clear();   
		m_tG711a.Clear();   
		m_tG722.Clear();    
		m_tG728.Clear();	   
		m_tG729.Clear();
		m_tMP3.Clear();
        m_tG7221c.Clear();
		m_tG719.Clear();
        m_tMpegAacLc.Clear();
        m_tMpegAacLd.Clear();
		
		m_tG7231.Clear();
		
		m_tT120.Clear();
		m_tH224.Clear();

        SetEncryptBits(emEncryptTypeNone);

        m_bIsSupportH239        = FALSE;
        m_bSupportRSVP          = FALSE;
		m_bSupportActiveH263Plus= FALSE;

        SetFECType((u8)emFECNone);

		m_bySubId               = 0;
		m_emH264NALMode         = emNALSignal;
	}

    void host2net(BOOL bhton)
    {
        for(s32 nIndex = 0; nIndex<MAX_CAPTABLE_SIZE; nIndex++)
        {
            if (m_awCapTable[nIndex] == 0)
                break;
            
            if (bhton) 
            {
                m_awCapTable[nIndex] = htons(m_awCapTable[nIndex]);
            }
            else
            {
                m_awCapTable[nIndex] = ntohs(m_awCapTable[nIndex]);
            }
        }
        
        s32 nDesCap = 0;
        s32 nSimuCap = 0;
        s32 nAltCap = 0;
        for(nDesCap = 0; nDesCap < MAX_DESCAP_NUM; nDesCap++)
        {
            for(nSimuCap = 0; nSimuCap < MAX_SIMUCAP_NUM; nSimuCap++)
            {
                for(nAltCap = 0; nAltCap < MAX_ALTCAP_NUM; nAltCap++)
                {
                    if (bhton)
                    {
                        m_aaawCapDesc[nDesCap][nSimuCap][nAltCap] 
                            = htons(m_aaawCapDesc[nDesCap][nSimuCap][nAltCap]);
                    }
                    else
                    {
                        m_aaawCapDesc[nDesCap][nSimuCap][nAltCap] 
                            = ntohs(m_aaawCapDesc[nDesCap][nSimuCap][nAltCap]);
                    }
                }
            }
        }

        m_tH261Cap.host2net(bhton);
        m_tH263Cap.host2net(bhton);
        m_tH263plusCap.host2net(bhton);
        for (u8 byLoop = 0; byLoop < MAX_H264CAP_NUM; byLoop++)
        {
            m_atH264Cap[byLoop].host2net(bhton);
        }

        m_tMpeg4Cap.host2net(bhton);
        m_tH262Cap.host2net(bhton);

        m_tG711u.host2net(bhton);
        m_tG711a.host2net(bhton);
        m_tG722.host2net(bhton);
        m_tG728.host2net(bhton);
        m_tG729.host2net(bhton);
        m_tMP3.host2net(bhton);
        m_tG7221c.host2net(bhton);  
		m_tG719.host2net(bhton);
        m_tG7231.host2net(bhton);
        m_tMpegAacLc.host2net(bhton);
        m_tMpegAacLd.host2net(bhton);

        m_tT120.host2net(bhton);
        m_tH224.host2net(bhton);

        m_bIsSupportH239 = htonl(m_bIsSupportH239);
        m_bSupportRSVP   = htonl(m_bSupportRSVP);    
		m_emH264NALMode  = (emH264NALMode)htonl((u32)m_emH264NALMode);
    }

    //����֧��RSVP����
    void SetSupportRSVP(BOOL bSupportRSVP)
    {
        m_bSupportRSVP = bSupportRSVP;
    }
    //�Ƿ�֧��RSVP
    BOOL IsSupportRSVP()
    {
        return m_bSupportRSVP;
    }

	//����֧��RSVP����
    void SetSupportActiveH263(BOOL bSupport)
    {
        m_bSupportActiveH263Plus = bSupport;
    }
    //�Ƿ�֧��RSVP
    BOOL IsSupportActiveH263()
    {
        return m_bSupportActiveH263Plus;
    }
    //����ǰ���������
    void SetFECType(u8 emType)
    {
        m_byFECBits = emType;
    }
    //��ȡǰ���������
    u8 GetFECType() const
    {
        return m_byFECBits;
    }
    /*�ϲ���ʱ��ʹ��*/
    void SetSupportH239(BOOL bSupporth239)
    {
        m_bIsSupportH239 = bSupporth239;
    }
    BOOL IsSupportH239()
    {
        return m_bIsSupportH239;
    }
    //
    //�����������������H.264��������⴫��SetH264VideoCapʱ��Ӧ�������±�
	BOOL SetCapDesc(u8 byCapIndex, u8 bySimuIndex, u8 byAltIndex, u16 wPayload, u8 byH264SubId = 0)
	{
		u16 wRealPt = wPayload&0xff;

		if( byCapIndex >= MAX_DESCAP_NUM || bySimuIndex >= MAX_SIMUCAP_NUM
			|| byAltIndex >= MAX_ALTCAP_NUM )
		{
			return FALSE;
		}

        if ( wRealPt == v_h264 && byH264SubId >= MAX_H264CAP_NUM )
        {
            return FALSE;
        }

		u16 byCapTableId = AddCapToTable(wPayload, byH264SubId);
		m_aaawCapDesc[byCapIndex][bySimuIndex][byAltIndex] = byCapTableId;
		if((wPayload&0xff) == v_h264)
		{
			m_awH264ToSubId[byCapTableId] = byH264SubId;
		}

        return TRUE;
	}
    //�õ�������    
	u16 GetCapDescId(u8 byCapIndex, u8 bySimuIndex, u8 byAltIndex)
	{
		if(byCapIndex >= MAX_DESCAP_NUM || bySimuIndex >= MAX_SIMUCAP_NUM
			|| byAltIndex >= MAX_ALTCAP_NUM )
		{
            //guzh 2008/06/02
			return 0xFFFF;
		}
		return m_aaawCapDesc[byCapIndex][bySimuIndex][byAltIndex];		
	}
    
    //ͬʱ���������ж�,pwPayloadȫ��������,nNum����������,ptH264Capȫ��H264����[in/out]
	BOOL IsExistsimultaneous(u16 *pwPayload, s32 nNum, TH264VideoCap* ptH264Cap=NULL, TAACCap *ptAacCap = NULL )
	{
		//���H264��TH264����������
		TH264VideoCap tH264;
		s32 nH264Num=0;
		s32 anH264Input[MAX_H264CAP_NUM];
        s32 i;
		if(ptH264Cap != NULL)
		{
			memset(anH264Input, 0xFF, MAX_H264CAP_NUM);
			for(i=0; i<nNum; i++)
			{
				if((pwPayload[i]&0xff) == v_h264)
				{
					nH264Num++;
				}
			}

// 			for(i=0; i<nH264Num; i++)
// 			{
// 				anH264Input[i] = i;
// 			}
// 
// 			for(i=0; i<nH264Num-1; i++)
// 			{
// 				for(s32 j=i+1; j<nH264Num; j++)
// 				{
// 					if(ptH264Cap[j] <= ptH264Cap[i])
// 					{
// 						tH264 = ptH264Cap[j];
// 						ptH264Cap[j] = ptH264Cap[i];
// 						ptH264Cap[i] = tH264;
// 
// 						temp = anH264Input[j];
//                         anH264Input[j] = anH264Input[i];
// 						anH264Input[i] = temp;
// 					}
// 				}
// 			}
		}
		
        //////////////////////////////////////////////////////////////////////////
        //Jacky Wei Print all inner the capabilities
        /*
        s32  nCapIndex  = 0, nSimuIndex=0, nAltIndex=0;
        OspPrintf(1, 0, "Inner capabilities:");   
        for (nCapIndex = 0; nCapIndex < MAX_DESCAP_NUM; nCapIndex++)
        {
            for(nSimuIndex=0; nSimuIndex < MAX_SIMUCAP_NUM; nSimuIndex++)
            {
                for(nAltIndex = 0; nAltIndex < MAX_ALTCAP_NUM; nAltIndex++)
                {
                    u16 wCapTableId = GetCapDescId(nCapIndex, nSimuIndex, nAltIndex);
                    if ( wCapTableId == 0xFFFF )
                        break;
                    u16 wPayloadType = m_awCapTable[wCapTableId];
                    if(wPayloadType == 0) 
                        break;
                    OspPrintf(1, 0, "    Payload:%d, (%d:%d:%d)\n", wPayloadType, nCapIndex, nSimuIndex, nAltIndex);
                }
            }
        }
        */
        //////////////////////////////////////////////////////////////////////////

        u16 awInterPayload[MAX_SIMUCAP_NUM]; //�����ⲿ�غ����͵�����
        memset(awInterPayload, 0, sizeof(awInterPayload));
        for(s32 nInterIndex = 0; nInterIndex < nNum; nInterIndex++)
        {
            awInterPayload[nInterIndex] = pwPayload[nInterIndex];
        }

        BOOL bRes = FALSE;
        for(s32 nH263Num = 0; nH263Num < 3; nH263Num++)
        {
            bRes = IsInterExistsimultaneous(awInterPayload, nNum, ptH264Cap, nH264Num, ptAacCap );
			//IsInterExistsimultaneous�����bug��û��239ʱ�����Ȱѵڶ�·��ʽ�ڵ�һ·���ҵ�
			//������Ҫ�������ٲ���һ����ȷ�����ս�� ruiyigen 091126
// 			if ( !bRes )
// 			{
// 				u16 awInterPayload2[MAX_SIMUCAP_NUM] = { 0 };
// 				int n = 0;
// 				for ( n = 0; n < nNum; n++ )
// 				{
// 					awInterPayload2[n] = m_awInterPayload[nNum - n - 1];					
// 				}
// 				bRes = IsInterExistsimultaneous(awInterPayload2, nNum, ptH264Cap, nH264Num);
// 			}
// 
// 				if(ptH264Cap != NULL)
// 				{
// 					TH264VideoCap atH264VideoCap[MAX_H264CAP_NUM];
// 					s32 i;
// 					for(i=0; i<nH264Num; i++)
// 					{
// 						atH264VideoCap[anH264Input[i]] = ptH264Cap[i];
// 					}
// 
// 					for(i=0; i<nH264Num; i++)
// 					{
// 						 ptH264Cap[i] = atH264VideoCap[i];
// 					}
// 				}
			if ( bRes == TRUE )
            {
				break;
            }
            
            //����ж�h263������ʧ�ܣ����ж�h263plus������
            s32 nIndex = 0;
            //assuming that we can match a H.263 or H.263+ video capability
            //bRes = TRUE;

            for(nIndex = 0; nIndex < nNum; nIndex++) 
            {
                if(awInterPayload[nIndex] == v_h263)
                {
                    awInterPayload[nIndex] = v_h263plus;
                    break;
                }
                else if(awInterPayload[nIndex] == GetH239Type(v_h263))
                {
                    awInterPayload[nIndex] = GetH239Type(v_h263plus);
                    break;
                }

                //////////////////////////////////////////////////////////////////////////
                /*
                else if(m_awInterPayload[nIndex] == GetH239Type(v_h263plus)
                    || m_awInterPayload[nIndex] == GetEType(v_h263plus,emEncryptTypeAES)
                    || m_awInterPayload[nIndex] == GetEType(v_h263plus,emEncryptTypeDES)
                    || m_awInterPayload[nIndex] == GetEType(v_h263plus,emEncryptTypeAES|emEncryptTypeDES))
                {
                    break;
                }
                */
                //////////////////////////////////////////////////////////////////////////

                else if(awInterPayload[nIndex] == GetEType(v_h263,emEncryptTypeAES))
                {
                    awInterPayload[nIndex] = GetEType(v_h263plus,emEncryptTypeAES);
                    break;
                }
                else if(awInterPayload[nIndex] == GetEType(v_h263,emEncryptTypeDES))
                {
                    awInterPayload[nIndex] = GetEType(v_h263plus,emEncryptTypeDES);
                    break;
                }
                else if(awInterPayload[nIndex] == GetEType(v_h263,emEncryptTypeAES|emEncryptTypeDES))
                {
                    awInterPayload[nIndex] = GetEType(v_h263plus,emEncryptTypeAES|emEncryptTypeDES);
                    break;
                }
                else if(awInterPayload[nIndex] == GetH239Type(GetEType(v_h263,emEncryptTypeAES)))
                {
                    awInterPayload[nIndex] = GetH239Type(GetEType(v_h263plus,emEncryptTypeAES));
                    break;
                }
                else if(awInterPayload[nIndex] == GetH239Type(GetEType(v_h263,emEncryptTypeDES)))
                {
                    awInterPayload[nIndex] = GetH239Type(GetEType(v_h263plus,emEncryptTypeDES));
                    break;
                }
                else if(awInterPayload[nIndex] == GetH239Type(GetEType(v_h263,emEncryptTypeAES|emEncryptTypeDES)))
                {
                    awInterPayload[nIndex] = GetH239Type(GetEType(v_h263plus, emEncryptTypeAES|emEncryptTypeDES));
                    break;
                }
                else
                {
                    bRes = FALSE;
                }
            }

            if (nIndex == nNum) //û��H263����
                return bRes;
        }

        return bRes;
	}
	
	//�õ�������
	u16 GetCapFromTable(u8 byCapIndex)
	{
		if(byCapIndex >= MAX_CAPTABLE_SIZE)
			return 0;
		return m_awCapTable[byCapIndex];
	};

	void SetCapToTable(u8 byCapIndex, u16 wPayload)
	{
		if(byCapIndex >= MAX_CAPTABLE_SIZE)
			return;
		m_awCapTable[byCapIndex] = wPayload;
	}

    //������Ƶ������.������H.264
	BOOL SetVideoCap(TVideoCap &tVideoCap, u16 wPayload)
	{
		switch(wPayload)
		{
		case v_h261:	 m_tH261Cap		= tVideoCap; break;
		case v_h263:	 m_tH263Cap		= tVideoCap; break;
		case v_h263plus: m_tH263plusCap = tVideoCap; break;		
		case v_mpeg4:	 m_tMpeg4Cap	= tVideoCap; break;
        case v_h262:	 m_tH262Cap	    = tVideoCap; break;
            
        case v_h264:
            OspPrintf(1, 0, "[H323Adp][TCapSet::SetVideoCap] Function depreciated!\n");
            //no return
		default: 
            return FALSE;
		}
		return TRUE;
	}
    //�õ���Ƶ������.������H.264
    TVideoCap* GetVideoCap(u16 wPayload)
    {
        TVideoCap *ptVideoCap = NULL;
        switch(wPayload)
        {
        case v_h261:	 ptVideoCap = &m_tH261Cap;		break;
        case v_h263:	 ptVideoCap = &m_tH263Cap;		break;
        case v_h263plus: ptVideoCap = &m_tH263plusCap;  break;        
        case v_mpeg4:	 ptVideoCap = &m_tMpeg4Cap;		break;
        case v_h262:	 ptVideoCap = &m_tH262Cap;		break;
        
        case v_h264:
             OspPrintf(1, 0, "[H323Adp][TCapSet::GetVideoCap] Function depreciated!\n");
             //no retuurn
        default:break;
        }
        return ptVideoCap;
    }
    //����H.264��Ƶ������,����ֵ��byH264SubId,��SetCapDescʱ��
    u8 SetH264VideoCap(TH264VideoCap &tVideoCap)
    {
        if (m_bySubId >= MAX_H264CAP_NUM)
        {
            return FALSE;
        }
		u8 byResult = m_bySubId;
		if(FindH264VideoCap(tVideoCap, byResult) == FALSE)
		{
			m_atH264Cap[m_bySubId++]= tVideoCap;
		}

		return byResult;
    }
    //�õ�H.264��Ƶ������
    TH264VideoCap* GetH264VideoCap(u8 bySubId)
    {
        if (bySubId >= MAX_H264CAP_NUM)
        {
            return NULL;
        }
        return &(m_atH264Cap[bySubId]);
    }
    //�õ�H264����
	u8 GetH264Num()
	{
		return m_bySubId;
	}

	//������G7231/AAC
	TAudioCap* GetAudioCap(u16 wPayload)
	{
		TAudioCap *ptAudioCap = NULL;
		switch(wPayload)
		{
		case a_g711u: ptAudioCap = &m_tG711u; break;
		case a_g711a: ptAudioCap = &m_tG711a; break;
		case a_g722:  ptAudioCap = &m_tG722;  break;
		case a_g728:  ptAudioCap = &m_tG728;  break;
		case a_g729:  ptAudioCap = &m_tG729;  break;
		case a_mp3:   ptAudioCap = &m_tMP3;   break;
        case a_g7221: ptAudioCap = &m_tG7221c;break;
		case a_g719:  ptAudioCap = &m_tG719;  break;//ruiyigen 20091012
		default:break;
		}
		return ptAudioCap;
	}
	//������G7231/AAC
	BOOL SetAudioCap(TAudioCap &tAudioCap, u16 wPayload)
	{
		switch(wPayload)
		{
		case a_g711u: m_tG711u = tAudioCap; break;
		case a_g711a: m_tG711a = tAudioCap; break;
		case a_g722:  m_tG722  = tAudioCap; break;
		case a_g728:  m_tG728  = tAudioCap; break;
		case a_g729:  m_tG729  = tAudioCap; break;
        case a_mp3:   m_tMP3   = tAudioCap; break;
        case a_g7221: m_tG7221c= tAudioCap; break;
		case a_g719:  m_tG719 = tAudioCap; break; //ruiyigen 20091012
		default: return FALSE; break;
		}
		return TRUE;
	}
	//G7231
	TG7231Cap* GetG7231Cap()
	{	
		return &m_tG7231;
	}
	//G7231
	BOOL SetG7231Cap(TG7231Cap &tG7231Cap)
	{
		m_tG7231 = tG7231Cap;
		return TRUE;
	}
    //AAC
    TAACCap* GetAACCap(u16 wPayload)
    {
        TAACCap *ptAudioCap = NULL;
        switch(wPayload)
        {
        case a_mpegaaclc: ptAudioCap = &m_tMpegAacLc;break;
        case a_mpegaacld: ptAudioCap = &m_tMpegAacLd;break;
        default:break;
        }
        return ptAudioCap;
    }
    //AAC
    BOOL SetAACCap(TAACCap &tAudioCap, u16 wPayload)
    {
        switch(wPayload)
        {
        case a_mpegaaclc: 
			{
				//m_tMpegAacLc = tAudioCap; break;
				m_tMpegAacLc.SetCapDirection( tAudioCap.GetCapDirection() );
				m_tMpegAacLc.SetChnl( static_cast<tagAACCap::emAACChnlCfg>(m_tMpegAacLc.GetChnl() | tAudioCap.GetChnl()) );
				break;
			}
        case a_mpegaacld: 
			{
				//m_tMpegAacLd = tAudioCap; break;
				m_tMpegAacLc.SetCapDirection( tAudioCap.GetCapDirection() );
				m_tMpegAacLd.SetChnl( static_cast<tagAACCap::emAACChnlCfg>(m_tMpegAacLd.GetChnl() | tAudioCap.GetChnl()) );
				break;
			}
            
        default: return FALSE; break;
        }
        return TRUE;
	}

	TDataCap* GetDataCap(u16 wPayload)
	{
		TDataCap *ptDataCap = NULL;
		switch(wPayload)
		{
		case d_t120: ptDataCap = &m_tT120; break;
		case d_h224: ptDataCap = &m_tH224; break;
		default:break;
		}
		return ptDataCap;
	}
	BOOL SetDataCap(TDataCap &tDataCap, u16 wPayload)
	{
		switch(wPayload)
		{
		case d_t120: m_tT120 = tDataCap; break;
		case d_h224: m_tH224 = tDataCap; break;
		default: return FALSE; break;
		}
		return TRUE;
	}

	/*�����ڷ���������ʱʹ��,��ʾͬʱ֧�ֵļ�������.
	 *��byEncryptBit=emEncryptTypeDES|emEncryptTypeAES;
	 */
	void SetEncryptBits( u8 byEncryptBits)
	{
		m_byEncryptBits = byEncryptBits;
	}
	u8 GetEncryptBits()
	{
		return m_byEncryptBits;
	}

	u8 GetSubId(u8 byCapIdex)
	{
		return m_awH264ToSubId[byCapIdex];
	}

	void SetH264NALMode(emH264NALMode emNALMode)
	{
		m_emH264NALMode = emNALMode;
	}

	emH264NALMode GetH264NALMode()
	{
		return m_emH264NALMode;
	}

	BOOL IsH264CapALessEqualB( const TH264VideoCap & tH264A, const TH264VideoCap & tH264B )
	{
		double dAMaxMBPS = .0;
		double dBMaxMBPS = .0;
		if ( tH264A.GetMaxStaticMBPs() != 0 )
		{
			double dAMaxMBPS = tH264A.GetMaxMBPS();
			double dAMaxFS = tH264A.GetMaxFS();
			double dAMaxStaticMBPS = tH264A.GetMaxStaticMBPs();
			dAMaxMBPS = 1.0 / ( ( ( 4.0 / dAMaxFS ) / dAMaxMBPS ) + ( ( ( dAMaxFS - 4.0 ) / dAMaxFS ) / dAMaxStaticMBPS ) );
		}
		else
		{
			dAMaxMBPS = tH264A.GetMaxMBPS();
		}

		if ( tH264B.GetMaxStaticMBPs() != 0 )
		{
			double dBMaxMBPS = tH264B.GetMaxMBPS();
			double dBMaxFS = tH264B.GetMaxFS();
			double dBMaxStaticMBPS = tH264B.GetMaxStaticMBPs();
			dBMaxMBPS = 1.0 / ( ( ( 4.0 / dBMaxFS ) / dBMaxMBPS ) + ( ( ( dBMaxFS - 4.0 ) / dBMaxFS ) / dBMaxStaticMBPS ) );
		}
		else
		{
			dBMaxMBPS = tH264B.GetMaxMBPS();
		}

		if( ( dAMaxMBPS <= dBMaxMBPS ) && ( tH264A.GetMaxFS() <= tH264B.GetMaxFS() ) && ( !tH264A.GetProfileValue()/*���tH264�ǿյ�,profileΪ��*/ || tH264A.GetProfileValue() >= tH264B.GetProfileValue() ) )
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
/*====================================================================
  �� �� ���� FindH264PeerBestSupport
  ��    �ܣ� ����ĳһ�ֱ����¶Զ���������֧�ֵ����֡�ʵ�TH264VideoCap�ṹ��
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� u16 *pwPayload     payload����
             s32 nNum           payload�����С
			 OUT BOOL &bStatic  ���ص�TH264VideoCap�ṹ�����Ƿ����staticMaxBPS
			 s32 nFirstPtIndex    ��һ·��Ƶ��payload�����е�����������һ·��h264Ϊ-1
			 s32 nSecondPtIndex   �ڶ�·��Ƶ��payload�����е����������޵ڶ�·Ϊ-1
			 TH264VideoCap* ptH264Cap ����������
  �� �� ֵ�� BOOL ƥ��ɹ�TRUE ʧ��FALSE
  ��ע��1������TH264VideoCap* ptH264Cap��INOUT���ͣ����Ǳ��㷨�з��ص�ptH264Cap��������һ������ֵ��Ч��
        ��Ϊֻ���ڵ�һ·�ɹ�����������²Ż᳢�Է��͵ڶ�·��������ptH264Cap[2]�е�ptH264Cap[0]��ֵ��
		�̶����Ƿ�ı䲻��ο���ptH264Cap[1]��ʾ�ڶ�·ƥ��ɹ���ֵ
		2������������H264������֧��
		3�������ڵ���IsExistsimultaneous()ʧ�ܵ�����µ��ñ�����
  --------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  20100830      1.0		    ������                   ����
======================================================================*/
	BOOL FindH264PeerBestSupport( u16 *pwPayload, s32 nNum, OUT BOOL &bStatic, s32 nFirstPtIndex = -1, s32 nSecondPtIndex = -1, INOUT TH264VideoCap* ptH264Cap = NULL )
	{
		TH264VideoCap tH264;
		s32 nH264Num=0;
//		s32 anH264Input[MAX_H264CAP_NUM];
		bStatic = FALSE;
		if ( -1 == nFirstPtIndex && -1 == nSecondPtIndex )
		{
			return FALSE;
		}
		if ( NULL == ptH264Cap )
		{
			return FALSE;
		}

		if ( nFirstPtIndex != -1 )
		{
			++nH264Num;
		}
		if ( nSecondPtIndex != -1 )
		{
			++nH264Num;
		}
		

        u16 m_awInterPayload[MAX_SIMUCAP_NUM]; //�����ⲿ�غ����͵�����
        for(s32 nInterIndex = 0; nInterIndex < nNum; nInterIndex++)
        {
            m_awInterPayload[nInterIndex] = pwPayload[nInterIndex];
        }

		///////////////////////////////////////////////////////////////////
		BOOL bUsedFlag[MAX_DESCAP_NUM][MAX_SIMUCAP_NUM];
		BOOL ab239Flag[MAX_DESCAP_NUM][MAX_SIMUCAP_NUM];
		
		BOOL abH264GoodFlag[MAX_H264CAP_NUM];
		memset(abH264GoodFlag, 0, sizeof(abH264GoodFlag));

		BOOL abH264BadFlag[MAX_H264CAP_NUM];
		memset(abH264BadFlag, 0, sizeof(abH264BadFlag));

		u8   anH264Index[MAX_H264CAP_NUM];
		
		TH264VideoCap atBadH264VideoCap[MAX_H264CAP_NUM];
		memset( atBadH264VideoCap, 0, sizeof( atBadH264VideoCap ) );
		
		TH264VideoCap atGoodH264VideoCap[MAX_H264CAP_NUM];
		memset( atGoodH264VideoCap, 0, sizeof( atGoodH264VideoCap ) );

		TH264VideoCap atEqualH264VideoCap[MAX_H264CAP_NUM];
		memset( atEqualH264VideoCap, 0, sizeof( atEqualH264VideoCap ) );
		
        s32  nCount = nNum;//���ڼ���
        s32 nCapIndex=0, nSimuIndex=0, nAltIndex=0;
		s32 nIndex = 0;
        for(nCapIndex = 0; nCapIndex < MAX_DESCAP_NUM; nCapIndex++)
        {
            nCount = nNum; //�ָ���ʼֵ
			nIndex = 0;
			memset(anH264Index, 0xFF, MAX_H264CAP_NUM);
			
			memset(bUsedFlag, 0, sizeof(bUsedFlag));
			memset( ab239Flag, 0, sizeof( ab239Flag ) );
            for(nSimuIndex=0; nSimuIndex < MAX_SIMUCAP_NUM; nSimuIndex++)
            {
				if ( bUsedFlag[nCapIndex][nSimuIndex] )
				{
					continue;
				}
				s32  nPtNum = 1;//���ݵ�ǰ��������Ƶ��ѡ����Ӧ��Pt
				BOOL bSingle = FALSE;
				if ( 2 == nH264Num )
				{
					if ( 0 == nIndex )
					{
						nPtNum = nFirstPtIndex;
					}
					else
					{
						nPtNum = nSecondPtIndex;
					}
				}
				else if ( 1 == nH264Num )
				{
					bSingle = TRUE;
					if ( nFirstPtIndex != -1 )
					{
						nPtNum = nFirstPtIndex;
					}
					else if ( nSecondPtIndex != -1 )
					{
						nPtNum = nSecondPtIndex;
					}
				}
				if ( -1 == nFirstPtIndex && -1 == nSecondPtIndex )
				{
					return FALSE;
				}
				s32 nTemp = 0;
				for ( ; nTemp < MAX_ALTCAP_NUM; ++nTemp )
				{
					u16 wCapTableId = GetCapDescId(nCapIndex,nSimuIndex,nAltIndex);

                    if ( wCapTableId == 0xFFFF )
                        break;
					u16 wPayloadType = m_awCapTable[wCapTableId];
                    if(wPayloadType == 0) 
                        break;
					if( IsH239Type( wPayloadType ) )
					{
						ab239Flag[nCapIndex][nSimuIndex] = TRUE;
					}
				}
                for(nAltIndex = 0; nAltIndex < MAX_ALTCAP_NUM; nAltIndex++)
                {
                    u16 wCapTableId = GetCapDescId(nCapIndex,nSimuIndex,nAltIndex);
    
                    if ( wCapTableId == 0xFFFF )
                        break;
					u16 wPayloadType = m_awCapTable[wCapTableId];
                    if(wPayloadType == 0) 
                        break;
                    BOOL t1 = IsH239Type( wPayloadType );
					BOOL t2 = IsH239Type( pwPayload[nPtNum] );
                    //���ж��Ƿ���H239����
                    if ( IsH239Type( wPayloadType ) != IsH239Type( pwPayload[nPtNum] ) )
                        continue;
					
					if ( ab239Flag[nCapIndex][nSimuIndex] && nFirstPtIndex == nPtNum )//����ǰ�ǵ�һ·����simuindex�ǵڶ�·������
					{
						break;
					}
                    //���ֽڰ��������ֽ����
                    if ( (((~(wPayloadType&0xff00))&(pwPayload[nPtNum]&0xff00)) == 0)
                        && ((wPayloadType&0xff) == (pwPayload[nPtNum]&0xff)) )
                    {
						if((wPayloadType&0xff) == v_h264 && ptH264Cap!=NULL)
						{
                            u8 bySubId=m_awH264ToSubId[wCapTableId];
							if(bySubId == 0xFF)
								break;
							//�ж������Ƿ�֧��
							
							if( IsH264CapALessEqualB( ptH264Cap[nIndex], m_atH264Cap[bySubId] ) )
							{
								
								bUsedFlag[nCapIndex][nSimuIndex] = TRUE;
								nSimuIndex = -1;//��������	
								abH264GoodFlag[nIndex] = TRUE;
								
								if ( IsH264CapALessEqualB( atGoodH264VideoCap[nIndex], m_atH264Cap[bySubId] ) )
								{
									atGoodH264VideoCap[nIndex] = m_atH264Cap[bySubId];
								}
							}
							else////////////////////.	
							{
								if( ptH264Cap[nIndex].GetMaxFS() <= m_atH264Cap[bySubId].GetMaxFS() )
								{
									if ( IsH264CapALessEqualB( atBadH264VideoCap[nIndex], m_atH264Cap[bySubId] ) )
									{
										abH264BadFlag[nIndex] = TRUE;
										atBadH264VideoCap[nIndex] = m_atH264Cap[bySubId];
									}
									if ( ptH264Cap[nIndex].GetMaxFS() == m_atH264Cap[bySubId].GetMaxFS() 
									    && IsH264CapALessEqualB(atEqualH264VideoCap[nIndex], m_atH264Cap[bySubId]) )
									{
										atEqualH264VideoCap[nIndex] = m_atH264Cap[bySubId];
									}
								}
							}//////////////////////
						}
                    }
                }
				if ( -1 == nSimuIndex )
				{
					--nCount;
					++nIndex;
					if ( 0 == nCount || bSingle || 2 == nIndex )
					{
						break;
					}
				}
            }
        }
		BOOL bGoodFind = FALSE;
		BOOL bBadFind  = FALSE;
		if ( 2 == nH264Num )
		{
			bGoodFind = abH264GoodFlag[1];
			bBadFind  = abH264BadFlag[1];
		}
		else
		{
			bGoodFind = abH264GoodFlag[0];
			bBadFind  = abH264BadFlag[0];
		}
		if ( !bGoodFind && !bBadFind )
		{
			return FALSE;
		}
		for ( int j = nH264Num - 1; j >= 0; --j )
		{
			if ( IsH264CapALessEqualB( atGoodH264VideoCap[j], atBadH264VideoCap[j] ) )
			{
				if ( ptH264Cap[j].GetMaxFS() == atEqualH264VideoCap[j].GetMaxFS() )
				{
					ptH264Cap[j] = atEqualH264VideoCap[j];
				}
				else
				{
					ptH264Cap[j] = atBadH264VideoCap[j];
				}
				
			}
			else
			{
				ptH264Cap[j] = atGoodH264VideoCap[j];
			}

			if ( ptH264Cap[j].GetMaxStaticMBPs() != 0 )
			{
				bStatic = TRUE;
			}
			break;
		}
		return TRUE;
		////////////////////////////////////////////////////////////////////////
	}

private:
	//�������������������Ϊ H.264����Ҫ����TH264VideoCap�����±꣬����ֵΪpayload��captable�е�����ֵ
	u16 AddCapToTable(u16 wPayload, u8 byH264SubId)
	{
		for(s32 i = 0; i < MAX_CAPTABLE_SIZE; i++)
		{
            u8 byH264Count = 0;
            // ����Ƿ��ظ�
			if(m_awCapTable[i] == wPayload)
            {
                if ((wPayload&0xff) != v_h264) 
                {
				    return i;
                }
				if(byH264SubId == m_awH264ToSubId[i])
				{
					return i;
				}
                byH264Count ++;
                if (byH264Count >= MAX_H264CAP_NUM)
                {
                    return 0xFFFF;
                }
            }
			
			if(m_awCapTable[i] == 0)
			{
				m_awCapTable[i] = wPayload;
				return i;
			}
		}
		return 0xFFFF;
	}
    
    BOOL IsInterExistsimultaneous( u16 *pwPayload, s32 nNum, TH264VideoCap* ptH264Cap=NULL, s32 nH264Num=0, TAACCap* ptAacCap = NULL )
    {
		//add by shigubin for DEBUG
		if( ptAacCap || ptH264Cap )
		{
			OspPrintf( TRUE, FALSE, "IsInterExistsimultaneous Payload IN Total caps: %d, (H264 caps: %d):\n", nNum, nH264Num);
			u8 h264Index = 0;
			for( u8 payloadNum = 0; payloadNum < nNum; payloadNum++ )
			{
				OspPrintf( TRUE,FALSE, "	No%d. payload %d\n", payloadNum+1, pwPayload[payloadNum] );
				switch( pwPayload[payloadNum]&0xff )
				{
				case a_mpegaaclc:
				case a_mpegaacld:
					{
						if( ptAacCap )
							OspPrintf( TRUE,FALSE, "		AAC  ChannelNum: %d   Sample: %d	   Bitrate: %d\n", (u8)ptAacCap->GetChnl(), (u8)ptAacCap->GetSampleFreq(), ptAacCap->GetBitrate() );
					}
					break;
				case v_h264:
					{
						if( (h264Index == nH264Num) || (!ptH264Cap) )
							break;
						TH264VideoCap tH264 = ptH264Cap[h264Index++];
						{
							OspPrintf( TRUE, FALSE, "		H264  Profile: %d Level: %d MBPS: %d FS: %d StatciMBPS: %d Bitrate: %d\n",
								tH264.GetProfileValue(), tH264.GetLevel(), tH264.GetMaxMBPS(), tH264.GetMaxFS(), tH264.GetMaxStaticMBPs(), tH264.GetBitRate() );
						}
					}
					break;
				default:
					break;
				}
			}
		}
		//add end 

        //BOOL bUsedFlag[MAX_DESCAP_NUM][MAX_SIMUCAP_NUM][MAX_ALTCAP_NUM] = {{0},{0},{0}};
		BOOL bUsedFlag  [MAX_DESCAP_NUM][MAX_SIMUCAP_NUM];
		BOOL ab239Flag  [MAX_DESCAP_NUM][MAX_SIMUCAP_NUM];
        BOOL bH264Flag  [MAX_H264CAP_NUM];
        u8   anH264Index[MAX_H264CAP_NUM];
        s32 nCount = nNum;//���ڼ���
		s32 nH264Count = 0;
        s32 nCapIndex=0, nSimuIndex=0, nAltIndex=0;
        for(nCapIndex = 0; nCapIndex < MAX_DESCAP_NUM; nCapIndex++)
        {
            nCount = 0; //�ָ���ʼֵ
			memset(anH264Index, 0xFF, MAX_H264CAP_NUM);
			memset(bH264Flag, 0, sizeof(bH264Flag));
			memset(bUsedFlag, 0, sizeof(bUsedFlag));
			memset(ab239Flag, 0, sizeof(ab239Flag));
			nH264Count = 0;
            for(nSimuIndex=0; nSimuIndex < MAX_SIMUCAP_NUM; nSimuIndex++)
            {
                for(nAltIndex = 0; nAltIndex < MAX_ALTCAP_NUM; nAltIndex++)
                {
                    u16 wCapTableId = GetCapDescId(nCapIndex,nSimuIndex,nAltIndex);
                    //guzh 2008/06/02
                    if ( wCapTableId == 0xFFFF )
                        break;
					u16 wPayloadType = m_awCapTable[wCapTableId];
                    if (wPayloadType == 0)
                        break;

                    //���ж��Ƿ���H239����
                    if ( IsH239Type( wPayloadType ) != IsH239Type( pwPayload[nCount] ) )
                        continue;

                    //���ֽڰ��������ֽ����
                    if ( (((~(wPayloadType&0xff00))&(pwPayload[nCount]&0xff00)) == 0)
                        && ((wPayloadType&0xff) == (pwPayload[nCount]&0xff)))
                    {
                        if (bUsedFlag[nCapIndex][nSimuIndex] == FALSE)
                        {
                            if ((wPayloadType&0xff) == v_h264 && ptH264Cap!=NULL)
                            {
                                u8 bySubId=m_awH264ToSubId[wCapTableId];
                                if (bySubId == 0xFF)
                                    break;
                                //�ж������Ƿ�֧��
                                //for(s32 i=nH264Num-1; i>=0; i--)
                                //{
                                if (nH264Count < nH264Num && bH264Flag[nH264Count] == FALSE && ptH264Cap[nH264Count] <= m_atH264Cap[bySubId])
                                {
                                    bH264Flag[nH264Count] = TRUE;
                                    ++nCount;
                                    bUsedFlag[nCapIndex][nSimuIndex] = TRUE;
                                    nSimuIndex = -1;//��������
                                    
                                    anH264Index[nH264Count] = bySubId;
                                    ++nH264Count;
                                    break;
                                }
                                //}
                            }
                            else
                            {
                                //������λ��ʾͨ�� add 2011 12 28
                                if (( (wPayloadType&0xff) == a_mpegaaclc || (wPayloadType&0xff) == a_mpegaacld ))
                                {
                                    TAACCap *ptLocAacCap = GetAACCap( (wPayloadType&0xff) );
                                    if( wPayloadType&0xff == a_mpegaaclc && ptAacCap != NULL )
                                    {
                                        if( ((~(ptLocAacCap->GetChnl()&0x7f)) & (ptAacCap->GetChnl()&0x7f)) != 0 )
                                            break;
                                    }
                                    else if( wPayloadType&0xff == a_mpegaacld && ptAacCap != NULL )
                                    {
                                        if( ((~(ptLocAacCap->GetChnl()&0x7f)) & (ptAacCap->GetChnl()&0x7f)) != 0 )
                                            break;
                                    }
                                }

                                OspPrintf(1, 0, "       [adapter][DEBUG] IsInterExistsimultaneous, Round:%d, payload matched: wPayloadType=%d!\r\n",nCapIndex, wPayloadType);

                                ++nCount;
                                bUsedFlag[nCapIndex][nSimuIndex] = TRUE;
                                nSimuIndex = -1;//��������
                                break;
                            }
                        } //fi (bUsedFlag[nCapIndex][nSimuIndex] == FALSE)
                    } //fi payload type���ֽڰ��������ֽ����
                } // for (nAltIndex = 0; nAltIndex < MAX_ALTCAP_NUM; nAltIndex++)

                //OspPrintf(1, 0, "   [adapter][DEBUG] IsInterExistsimultaneous, Round:%d, matched:%d/%d, matched h264 cap: %d!\r\n", nCapIndex, nCount, nNum, nH264Num);

                if (nCount == nNum)
                {
					for (s32 i=0; i<nH264Num; i++)
					{
						ptH264Cap[i] = m_atH264Cap[anH264Index[i]];
						OspPrintf(1, 0, "   MaxMBPS is %d, MaxFS is %d, BitRate is %d\r\n", ptH264Cap[i].GetMaxMBPS(), ptH264Cap[i].GetMaxFS(),ptH264Cap[i].GetBitRate() );
					}
                    return TRUE;
                }
            } // for(nSimuIndex=0; nSimuIndex < MAX_SIMUCAP_NUM; nSimuIndex++)
        } // for(nCapIndex = 0; nCapIndex < MAX_DESCAP_NUM; nCapIndex++)

        return FALSE;
    }

    BOOL FindH264VideoCap(TH264VideoCap& tH264VideoCap, u8& bySubId)
	{
		for (u8 i=0; i<m_bySubId; i++)
		{
			if (m_atH264Cap[i] == tH264VideoCap)
			{
				bySubId = i;
				return TRUE;
			}
		}
		return FALSE;
	}
}TCapSet;


//temporal spatial tradeoff
typedef struct tagTSTO
{
	u8  m_chIsCommand;     //�����ָʾ
    u8  m_chTradeoffValue; //The trade off value, between 0(high spatial resolution) to 31(a high frame rate)

    tagTSTO()
	{
		Clear();
	}

	void Clear()
	{
		m_chIsCommand = 0;
		m_chTradeoffValue = 0;
	}

	void SetIsCommand(BOOL bCommand)
	{
		m_chIsCommand = bCommand ? 1:0;
	}
	BOOL IsCommand()
	{
		return m_chIsCommand>0;
	}
	//set The trade off value, between 0 to 31.
	void SetTradeoffValue(u8 byTradeoffValue)
	{
		if( byTradeoffValue > 31 )
		{
           return ;
		}
        m_chTradeoffValue = byTradeoffValue;
	}

	s8 GetTradeoffValue()
	{
		return m_chTradeoffValue;
	}
}TTSTO;


//update GOB struct
typedef struct tagVFUGOB
{
	s32 m_nFirstGOB;
	s32 m_nNumOfGOB;

	tagVFUGOB()
	{
		Clear();
	}

	void Clear()
	{
		m_nFirstGOB = 0;
		m_nNumOfGOB = 0;
	}

    void host2net(BOOL bhton)
    {
        if (bhton)
        {
            m_nFirstGOB = htonl(m_nFirstGOB);
            m_nNumOfGOB = htonl(m_nNumOfGOB);
        }
        else
        {
            m_nFirstGOB = ntohl(m_nFirstGOB);
            m_nNumOfGOB = ntohl(m_nNumOfGOB);
        }
    }

    void SetFirstGOB(s32 nFirstGOB)
	{
		m_nFirstGOB = nFirstGOB;
	}
	s32 GetFirstGOB()
	{
		return m_nFirstGOB;
	}
	void SetNumOfGOB(s32 nNumOfGOB)
	{
		//add by yj
		//m_nNumOfGOB = m_nNumOfGOB;
		m_nNumOfGOB = nNumOfGOB;
		//end
	}
	s32 GetNumOfGOB()
	{
		return m_nNumOfGOB;
	}

}TVFUGOB;

//update MB struct
typedef struct tagVFUMB
{
	s32 m_nFirstGOB;
	s32 m_nFirstMB;
	s32 m_nNumOfMB;

	tagVFUMB()
	{
		Clear();
	}

	void Clear()
	{
		m_nFirstGOB = 0;
		m_nFirstMB	= 0;
		m_nNumOfMB	= 0;
	}

    void host2net(BOOL bhton)
    {
        if (bhton)
        {
            m_nFirstGOB = htonl(m_nFirstGOB);
            m_nFirstMB  = htonl(m_nFirstMB);
            m_nNumOfMB  = htonl(m_nNumOfMB);
        }
        else
        {
            m_nFirstGOB = ntohl(m_nFirstGOB);
            m_nFirstMB  = ntohl(m_nFirstMB);
            m_nNumOfMB  = ntohl(m_nNumOfMB);
        }
    }

    void SetFirstGOB(s32 nFirstGOB)
	{
		m_nFirstGOB = nFirstGOB;
	}
	s32 GetFirstGOB()
	{
		return m_nFirstGOB;
	}

	void SetFirstMB(s32 nFirstMB)
	{
		m_nFirstMB = nFirstMB;
	}
	s32 GetFirstMB()
	{
		return m_nFirstMB;
	}

	void SetNumOfMB(s32 nNumOfMB)
	{
		//add by yj
		//m_nNumOfMB = m_nNumOfMB;
		m_nNumOfMB = nNumOfMB;
		//end
	}
	s32 GetNumOfMB()
	{
		return m_nNumOfMB;
	}
	
}TVFUMB;

typedef struct tagPassRsp
{
	TTERLABEL m_tTer;
	s32       m_nPassLen;
	u8        m_abyPassword[LEN_H243PWD+1]; 

	tagPassRsp()
	{
		Clear();
	}

	void Clear()
	{
		memset( &m_tTer, 0, sizeof(m_tTer) );
		m_nPassLen = 0;
		memset( m_abyPassword, 0, sizeof(m_abyPassword) );
	}

    void host2net(BOOL bhton)
    {
        if (bhton)
        {
            m_nPassLen  = htonl(m_nPassLen);
        }
        else
        {
            m_nPassLen  = ntohl(m_nPassLen);
        }
    }

	//����TTERLABEL
	void SetTerLabel( TTERLABEL &tTerLabel )
	{
		m_tTer = tTerLabel;
	}
	//��ȡTTERLABEL
	TTERLABEL& GetTerlabel()
	{
		return m_tTer;
	}
	
	//����Password
	void SetPassword( u8 *pPassword, u16 wLen )
	{
		if ( pPassword != NULL && wLen < LEN_H243PWD+1 ) 
		{
			memset( m_abyPassword, 0, sizeof(m_abyPassword) );
			memcpy( m_abyPassword, pPassword, wLen );
			m_abyPassword[wLen] = '\0';
            m_nPassLen = wLen;
		}
	}
	//��ȡPassword
	u16 GetPassword( u8 *pbyPassword, u16 &wLen )
	{
		if ( pbyPassword != NULL ) 
		{
			u16 realLen = min( wLen, LEN_H243PWD );
			memcpy( pbyPassword, m_abyPassword, realLen );
			return realLen;
		}
	}	
}TPassRsp;

//H221�Ǳ����
typedef struct tagH221NonStandard
{
	u8		m_byT35CountryCode;
	u8		m_byT35Extension;
	u16		m_wManufacturerCode;

	void Clear()
	{
		m_byT35CountryCode	 = 0;
		m_byT35Extension	 = 0;
		m_wManufacturerCode  = 0;
	}

	void SetH221NonStandard( u8 byCountryCode, u8 byExtension, u16 wManufacturerCode)
	{
		m_byT35CountryCode	= byCountryCode;
		m_byT35Extension	= byExtension;
		m_wManufacturerCode = wManufacturerCode;
	}
	u8 GetT35CountryCode()
	{
		return m_byT35CountryCode;
	}
	u8 GetT35Extension()
	{
		return m_byT35Extension;
	}
	u16 GetManufacturerCode()
	{
		return m_wManufacturerCode;
	}
}TH221NONSTANDARD,*PTH221NONSTANDARD;

//���̱�ʶ��Ϣ
typedef struct tagVendorInfo
{
	TH221NONSTANDARD	m_tVendor;
	s8					m_achProductId[MAX_ProductIDSize+1];
	s8					m_achVersionId[MAX_VersionIdSize+1];

	tagVendorInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_tVendor.Clear();
		memset( m_achProductId, 0, sizeof(m_achProductId) );
		memset( m_achVersionId, 0, sizeof(m_achVersionId) );
	}

	void SetH221NonStandard( TH221NONSTANDARD &tVendor)
	{
		m_tVendor = tVendor;
	}
	TH221NONSTANDARD& GetH221NonStandard()
	{
		return m_tVendor;
	}

	void SetVendorID( s8 *pProductId, s8 *pVersionId )
	{
		strncpy( m_achProductId, pProductId, min(strlen(pProductId), MAX_ProductIDSize));
		strncpy( m_achVersionId, pVersionId, min(strlen(pVersionId), MAX_VersionIdSize));		
	}
	s8* GetProductID()
	{
		return m_achProductId;
	}
	s8* GetVersionID()
	{
		return m_achVersionId;
	}
}TVENDORINFO,*PTVENDORINFO;


//MultiplexCapability
typedef struct tagMultiplexCapability
{
	emH264NALMode m_emH264NALMode;

	tagMultiplexCapability()
	{
		Clear();
	}
	
	void Clear()
	{
		m_emH264NALMode = emNALNode;
	}
	
	void SetH264NALMode( emH264NALMode emNALMode)
	{
		m_emH264NALMode = emNALMode;
	}
	emH264NALMode& GetH264NALMode()
	{
		return m_emH264NALMode;
	}

}TMultiplexCapability,*PTMultiplexCapability;

//RAS��Ϣ�ṹ
//RRQ
typedef struct tagRRQInfo
{
	TNETADDR		m_tCallAddr;			//���������ַ
	TNETADDR		m_tLocalRASAddr;		//����RAS��ַ
	cmEndpointType	m_eTerminalType;		//�ն�����,GK��
	TALIASADDR		m_atAlias[MAXALIASNUM];	//��GKע��ʱ�Ķ������
	s32				m_nTimetoLive;			//timetolive����λ����	(optional)
	BOOL			m_bKeepAlive;			//������ע���־λ
	TALIASADDR		m_tEndpointID;			//�ն�ID,GK��			(optional)
	TNETADDR		m_tGkAddr;				//GK��ַ
	s8				m_ach_UserName[REG_NAME_LEN];			//ע���ʺ�(E164)
	s8				m_ach_Password[REG_PWD_LEN];			//ע����Կ
	TALIASADDR		m_tGKID;				//GK ID,GK��
	BOOL            m_bSigTraversal;        //signalling traversal
 	BOOL			m_bRequireGKPermison;

	s32				m_nProductIdSize;
	u8				m_abyProductId[LEN_256];				//��Ʒ��
	s32				m_nVerIdSize;
	u8				m_abyVersionId[LEN_256];				//�汾��

	tagRRQInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_tCallAddr.Clear();
		m_tLocalRASAddr.Clear();
		m_eTerminalType = cmEndpointTypeTerminal;
		memset( m_atAlias,0,sizeof(m_atAlias));
		m_nTimetoLive = 0;
		m_tGkAddr.Clear();
		memset(&m_tEndpointID,0,sizeof(TALIASADDR));
		memset(m_ach_UserName, 0, sizeof(m_ach_UserName));
		memset(m_ach_Password, 0, sizeof(m_ach_Password));
		m_bKeepAlive = FALSE;
		m_tCallAddr.SetNetAddress( 0, CALLPORT );
		m_tLocalRASAddr.SetNetAddress( 0, RASPORT );
		m_tGkAddr.SetNetAddress( 0, RASPORT );
		memset(&m_tGKID,0,sizeof(TALIASADDR));
		m_bSigTraversal = FALSE;
		m_bRequireGKPermison = FALSE;
		m_nProductIdSize = 0;
		m_nVerIdSize = 0;
		memset(m_abyProductId , 0 , LEN_256);
		memset(m_abyVersionId , 0 , LEN_256);
	}	
	
    //���ú��������ַ
    void SetCallAddr( TNETADDR &tCallAddr )
    {
        m_tCallAddr = tCallAddr;
    }
    //�õ����������ַ
    TNETADDR& GetCallAddr()
    {
        return m_tCallAddr;
    }

    //���ñ���RAS��ַ
    void SetLocalRASAddr( TNETADDR &tLocalRASAddr )
    {
        m_tLocalRASAddr = tLocalRASAddr;
    }
    //�õ�����RAS��ַ
    TNETADDR& GetLocalRASAddr()
    {
        return m_tLocalRASAddr;
    }

    //�����ն�����
    void SetTerminalType( cmEndpointType emTerminalType )
    {
        m_eTerminalType = emTerminalType;
    }
    //�õ��ն�����
    cmEndpointType GetTerminalType()
    {
        return m_eTerminalType;
    }

    //����ע�����
    void SetRRQAlias( TALIASADDR &tAlias, u8 byAliasNo )
    {
        if ( byAliasNo >= MAXALIASNUM )
            return;
        
        m_atAlias[byAliasNo] = tAlias;
    }
    //�õ�ע��ı���
    TALIASADDR& GetRRQAlias( u8 byAliasNo )
    {
        if ( byAliasNo < MAXALIASNUM ) 
            return m_atAlias[byAliasNo];
        else
            return m_atAlias[0];        
    }

    //����TimetoLiveֵ
    void SetTimetoLive( s32 nTimetoLive )
    {
        m_nTimetoLive = nTimetoLive;
    }
    //�õ�TimetoLiveֵ
    s32 GetTimetoLive()
    {
        return m_nTimetoLive;
    }

    //�����Ƿ�������ע��
    void SetKeepAlive( BOOL bKeepAlive )
    {
        m_bKeepAlive = bKeepAlive;
    }
    //�ж��Ƿ�������ע��
    BOOL IsKeepAlive()
    {
        return m_bKeepAlive;
    }

    //�����ն�ID
    void SetEndpointID( TALIASADDR &tEndpointID )
    {
        m_tEndpointID = tEndpointID;
    }
    //�õ��ն�ID
    TALIASADDR& GetEndpointID()
    {
        return m_tEndpointID;
    }
	//�����û�����
	void SetUserInfo(s8* pszUserName, s8* pszPassword)
	{
		if (pszUserName == NULL)
		{
			return;
		}
		memset(m_ach_UserName, 0, sizeof(m_ach_UserName));
		u16 nameLen = min( strlen(pszUserName), REG_NAME_LEN);
		strncpy(m_ach_UserName, pszUserName, nameLen);
		m_ach_UserName[nameLen] = '\0';
		
		if (pszPassword != NULL)
		{
			memset(m_ach_Password, 0, sizeof(m_ach_Password));
			u16 pwdLen = min(strlen(pszPassword), REG_PWD_LEN);
			strncpy(m_ach_Password, pszPassword, pwdLen);
			m_ach_Password[pwdLen] = '\0';
		}
		
	}
	//ȡ�û���
	s8* GetUserName()
	{
		return m_ach_UserName;
	}
	//ȡ����
	s8* GetPassword()
	{
		return m_ach_Password;
	}
    //����GK��ַ
    void SetGKAddr( TNETADDR &tGkAddr )
    {
        m_tGkAddr = tGkAddr;
    }
    //�õ�GK��ַ
    TNETADDR& GetGKAddr()
    {
        return m_tGkAddr;
    }
    //����GK ID
    void SetGKID( TALIASADDR &tGKID )
    {
        m_tGKID = tGKID;
    }
    //�õ�GK ID
    TALIASADDR& GetGKID()
    {
        return m_tGKID;
    }
	//���ò�Ʒ��
	void SetProductId(u8 *pbyId, s32 nLen)
	{
		if(pbyId == NULL|| nLen <= 0 )
		{
			return ;
		}
		memset( m_abyProductId, 0, sizeof(m_abyProductId) );
		s32 nReal = min(max(LEN_1, nLen), LEN_256);
		m_nProductIdSize = nReal;
        if(nLen >= LEN_1)
		{
			memcpy(m_abyProductId, pbyId, nReal);
		}
	}
	//��ȡ��Ʒ�ų���
	s32 GetProductIdSize()
	{
		return m_nProductIdSize;
	}
	//��ȡ��Ʒ��
	s32 GetProductId(u8 *pbyId, s32 nLen)
	{
		if(pbyId == NULL|| nLen <= 0 )
		{
			return 0;
		}
		s32 nReal = min(nLen, m_nProductIdSize); 
		memcpy(pbyId, m_abyProductId, nReal);
		return nReal;
	}
	//���ð汾��	
	void SetVersionId(u8 *pbyId, s32 nLen)
	{
		if(pbyId == NULL|| nLen <= 0 )
		{
			return ;
		}
		memset( m_abyVersionId, 0, sizeof(m_abyVersionId) );
		s32 nReal = min(max(LEN_1, nLen), LEN_256);
		m_nVerIdSize = nReal;
        if(nLen >= LEN_1)
		{
			memcpy(m_abyVersionId, pbyId, nReal);
		}
	}
	//��ȡ�汾�ų���
	s32 GetVersionIdSize()
	{
		return m_nVerIdSize;
	}
	//��ȡ�汾��
	s32 GetVersionId(u8 *pbyId, s32 nLen)
	{
		if(pbyId == NULL|| nLen <= 0 )
		{
			return 0;
		}
		s32 nReal = min(nLen, m_nVerIdSize); 
		memcpy(pbyId, m_abyVersionId, nReal);
		return nReal;
	}

}TRRQINFO, *PTRRQINFO;

//RCF
typedef struct tagRCFInfo
{
	TNETADDR		m_tCallSignalAddr;		//GK���صĺ��������ַ
	TALIASADDR		m_atAlias[MAXALIASNUM];	//GK���صĶ������			(optional)
	TALIASADDR		m_tGKID;				//GK ID,GK��
	TALIASADDR		m_tEndpointID;			//�ն�ID,GK��
	s32				m_nTimetoLive;			//timetolive ��λ����		(optional)
	BOOL			m_bWillRespondToIRR;	//�Ƿ���ӦIRR��Ϣ,GK��
	BOOL            m_bIsKDVTSGK;           //�Ƿ���KDVTS��GK
	BOOL            m_bSigTraversal;        //signalling traversal
	BOOL            m_bIfAccess;
	tagRCFInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_tCallSignalAddr.Clear();
		memset(m_atAlias,0,sizeof(m_atAlias));
		memset(&m_tGKID,0,sizeof(TALIASADDR));
		memset(&m_tEndpointID,0,sizeof(TALIASADDR));
		m_tCallSignalAddr.SetNetAddress( 0, CALLPORT );
		m_nTimetoLive = 0;
		m_bWillRespondToIRR = FALSE;
		m_bIsKDVTSGK = FALSE;
		m_bSigTraversal = FALSE;
		m_bIfAccess = FALSE;
	}

    //����GK���صĺ��������ַ
    void SetCallSignalAddr( TNETADDR &tCallSignalAddr )
    {
        m_tCallSignalAddr = tCallSignalAddr;
    }
    //�õ�GK���صĺ��������ַ
    TNETADDR& GetCallSignalAddr()
    {
        return m_tCallSignalAddr;
    }

    //����GK���صĶ������
    void SetRCFAlias( TALIASADDR &tAlias, u8 byAliasNo )
    {
        if ( byAliasNo >= MAXALIASNUM )
            return;
        
        m_atAlias[byAliasNo] = tAlias;
    }
    //�õ�GK���صĶ������
    TALIASADDR& GetRCFAlias( u8 byAliasNo )
    {
        if ( byAliasNo < MAXALIASNUM ) 
            return m_atAlias[byAliasNo];
        else
            return m_atAlias[0];
    }

    //����GK ID
    void SetGKID( TALIASADDR &tGKID )
    {
        m_tGKID = tGKID;
    }
    //�õ�GK ID
    TALIASADDR& GetGKID()
    {
        return m_tGKID;
    }
    
    //�����ն�ID
    void SetEndpointID( TALIASADDR &tEndpointID )
    {
        m_tEndpointID = tEndpointID;
    }
    //�õ��ն�ID
    TALIASADDR& GetEndpointID()
    {
        return m_tEndpointID;
    }

    //����TimetoLiveֵ
    void SetTimetoLive( s32 nTimetoLive )
    {
        m_nTimetoLive = nTimetoLive;
    }
    //�õ�TimetoLiveֵ
    s32 GetTimetoLive()
    {
        return m_nTimetoLive;
    }

    //�����Ƿ���ӦIRR��Ϣ
    void SetWillRespondToIRR( BOOL bKeepAlive )
    {
        m_bWillRespondToIRR = bKeepAlive;
    }
    //�ж��Ƿ���ӦIRR��Ϣ
    BOOL IsWillRespondToIRR()
    {
        return m_bWillRespondToIRR;
    }
	void SetIsKDVTSGK(BOOL bIsKDVGK)
	{
		m_bIsKDVTSGK = bIsKDVGK;
	}
	BOOL GetIsKDVTSGK()
	{
		return m_bIsKDVTSGK;
    }
}TRCFINFO, *PTRCFINFO;

//ARQ
typedef struct tagARQInfo
{
	cmCallType		m_eCallType;			    //��������,GK��
	cmCallModelType m_eCallModel;			    //GK����ģʽ,Ĭ��ֵΪֱ�Ӻ���	(optional)
	TALIASADDR		m_tEndpointID;			    //�ն�ID,GK��
	TALIASADDR		m_tDestAlias;			    //Ŀ�Ķ˱���
	TNETADDR		m_tCalledAddr;			    //Ŀ�Ķ˵�ַ
	TALIASADDR		m_atSrcAlias[MAXALIASNUM];  //Դ�˱���
	TNETADDR		m_tCallAddr;			    //Դ�˵�ַ,GK��					(optional)
	s32				m_nBandWidth;			    //��λ��kbps
	s32				m_nCRV;					    //���вο�ֵ,GK��
	s8  			m_achConferenceID[LEN_GUID];//����ID,GK��
	BOOL			m_bAnswerCall;			    //�Ƿ񱻽�,GK��
	s8  			m_achCallID[LEN_GUID];	    //����ID,GK��
	TALIASADDR		m_tGKID;				    //GK ID,GK��					(optional)
	
	TNETADDR		m_tGkAddr;				    //GK��ַ
	
	tagARQInfo()
	{
		Clear();
	}

	void Clear()
	{
		memset(&m_tEndpointID,0,sizeof(TALIASADDR));
		memset(&m_tGKID,0,sizeof(TALIASADDR));
		memset(m_achCallID,0,sizeof(m_achCallID));
		memset(m_achConferenceID,0,sizeof(m_achConferenceID));
		memset(&m_tDestAlias,0,sizeof(TALIASADDR));
		memset(m_atSrcAlias,0,sizeof(m_atSrcAlias));
		m_tCalledAddr.Clear();
		m_tCallAddr.Clear();		
		m_tGkAddr.Clear();
		m_eCallType = cmCallTypeP2P;
		m_eCallModel = cmCallModelTypeDirect;
		m_nBandWidth = 2000;
		m_nCRV = 0;
		m_bAnswerCall = FALSE;
		m_tCalledAddr.SetNetAddress( 0, CALLPORT );
		m_tGkAddr.SetNetAddress( 0, RASPORT );
	}

    //���ú�������
    void SetCallType( cmCallType emCallType )
    {
        m_eCallType = emCallType;
    }
    //�õ���������
    cmCallType GetCallType()
    { 
        return m_eCallType;
    }

    //���ú���ģʽ
    void SetCallModelType( cmCallModelType emCallModel )
    {
        m_eCallModel = emCallModel;
    }
    //�õ�����ģʽ
    cmCallModelType GetCallModelType()
    { 
        return m_eCallModel;
    }

    //�����ն�ID
    void SetEndpointID( TALIASADDR &tEndpointID )
    {
        m_tEndpointID = tEndpointID;
    }
    //�õ��ն�ID
    TALIASADDR& GetEndpointID()
    {
        return m_tEndpointID;
    }

    //����Ŀ�Ķ˱���
    void SetDestAlias( TALIASADDR &tDestAlias )
    {
        m_tDestAlias = tDestAlias;
    }
    //�õ�Ŀ�Ķ˱���
    TALIASADDR& GetDestAlias()
    {
        return m_tDestAlias;
    }

    //����Ŀ�Ķ˵�ַ
    void SetCalledAddr( TNETADDR &tCalledAddr )
    {
        m_tCalledAddr = tCalledAddr;
    }
    //�õ�Ŀ�Ķ˵�ַ
    TNETADDR& GetCalledAddr()
    {
        return m_tCalledAddr;
    }

    //����Դ�˱���
    void SetARQSrcAlias( TALIASADDR &tAlias, u8 byAliasNo )
    {
        if ( byAliasNo >= MAXALIASNUM )
            return;
        
        m_atSrcAlias[byAliasNo] = tAlias;
    }
    //�õ�Դ�˱���
    TALIASADDR& GetARQSrcAlias( u8 byAliasNo )
    {
        if ( byAliasNo < MAXALIASNUM ) 
            return m_atSrcAlias[byAliasNo];
        else
            return m_atSrcAlias[0];
    }

    //����Դ�˵�ַ
    void SetCallAddr( TNETADDR &tCallAddr )
    {
        m_tCallAddr = tCallAddr;
    }
    //�õ�Դ�˵�ַ
    TNETADDR& GetCallAddr()
    {
        return m_tCallAddr;
    }

    //���ô���
    void SetBandWidth( s32 nBandWidth )
    {
        m_nBandWidth = nBandWidth;
    }
    //�õ�����
    s32 GetBandWidth()
    {
        return m_nBandWidth;
    }

    //���ú��вο�ֵ
    void SetCRV( s32 nCRV )
    {
        m_nCRV = nCRV;
    }
    //�õ����вο�ֵ
    s32 GetCRV()
    {
        return m_nCRV;
    }

    //���û���ID
    void SetConferenceID( s8 *pchConferenceID, u8 byLen )
    {
        if ( pchConferenceID == NULL )
            return;
        
        memset( m_achConferenceID, 0, sizeof(m_achConferenceID) );
        u8 byRealLen = min( byLen, LEN_GUID );
        strncpy( m_achConferenceID, pchConferenceID, byRealLen );
        m_achConferenceID[byRealLen] = '\0';
    }
    //�õ�����ID
    s8* GetConferenceID()
    {
        return m_achConferenceID;
    }

    //�����Ƿ񱻽�
    void SetAnswerCall( BOOL bAnswerCall )
    {
        m_bAnswerCall = bAnswerCall;
    }
    //�ж��Ƿ񱻽�
    BOOL IsAnswerCall()
    {
        return m_bAnswerCall;
    }

    //���ú���ID
    void SetCallID( s8 *pchCallID, u8 byLen )
    {
        if ( pchCallID == NULL )
            return;
        
        memset( m_achCallID, 0, sizeof(m_achCallID) );
        u8 byRealLen = min( byLen, LEN_GUID );
        strncpy( m_achCallID, pchCallID, byRealLen );
        m_achCallID[byRealLen] = '\0';
    }
    //�õ�����ID
    s8* GetCallID()
    {
        return m_achCallID;
    }

    //����GK ID
    void SetGKID( TALIASADDR &tGKID )
    {
        m_tGKID = tGKID;
    }
    //�õ�GK ID
    TALIASADDR& GetGKID()
    {
        return m_tGKID;
    }

    //����GK��ַ
    void SetGKAddr( TNETADDR &tGKAddr )
    {
        m_tGkAddr = tGKAddr;
    }
    //�õ�GK��ַ
    TNETADDR& GetGKAddr()
    {
        return m_tGkAddr;
    }    
}TARQINFO, *PTARQINFO;

//ACF
typedef struct tagACFInfo
{
	s32				m_nBandWidth;			    //��λ��kbps
	cmCallModelType m_eCallModel;			    //GK����ģʽ,Ĭ��ֵΪֱ�Ӻ���
	TNETADDR		m_tCalledAddr;			    //Ŀ�Ķ˵�ַ
	s32				m_nIRRFrequency;		    //IRR�ķ���Ƶ�ʣ���λ����	(optional)
	BOOL			m_bWillResponseIRR;		    //��ӦIRR��Ϣ
	TALIASADDR		m_atDestAlias[MAXALIASNUM];	//GK���صĶ������			(optional) 
	
	tagACFInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_tCalledAddr.Clear();
		m_nBandWidth = 4000;
		m_eCallModel = cmCallModelTypeDirect;
		m_nIRRFrequency = 0;
		m_bWillResponseIRR = FALSE;
		m_tCalledAddr.SetNetAddress( 0, CALLPORT );
		memset(m_atDestAlias,0,sizeof(m_atDestAlias));
	}

    //���ô���
    void SetBandWidth( s32 nBandWidth )
    {
        m_nBandWidth = nBandWidth;
    }
    //�õ�����
    s32 GetBandWidth()
    {
        return m_nBandWidth;
    }

    //���ú���ģʽ
    void SetCallModelType( cmCallModelType emCallModel )
    {
        m_eCallModel = emCallModel;
    }
    //�õ�����ģʽ
    cmCallModelType GetCallModelType()
    { 
        return m_eCallModel;
    }

    //����Ŀ�Ķ˵�ַ
    void SetCalledAddr( TNETADDR &tCalledAddr )
    {
        m_tCalledAddr = tCalledAddr;
    }
    //�õ�Ŀ�Ķ˵�ַ
    TNETADDR& GetCalledAddr()
    {
        return m_tCalledAddr;
    }

    //����IRR�ķ���Ƶ��
    void SetIRRFrequency( s32 nIRRFrequency )
    {
        m_nIRRFrequency = nIRRFrequency;
    }
    //�õ�IRR�ķ���Ƶ��
    s32 GetIRRFrequency()
    {
        return m_nIRRFrequency;
    }

    //�����Ƿ���ӦIRR��Ϣ
    void SetWillResponseIRR( BOOL bWillResponseIRR )
    {
        m_bWillResponseIRR = bWillResponseIRR;
    }
    //�ж��Ƿ���ӦIRR��Ϣ
    BOOL IsWillResponseIRR()
    {
        return m_bWillResponseIRR;
    }
    //����GK���صĶ������
    void SetACFAlias( TALIASADDR &tAlias, u8 byAliasNo )
    {
        if ( byAliasNo >= MAXALIASNUM )
            return;
        
        m_atDestAlias[byAliasNo] = tAlias;
    }
    //�õ�GK���صĶ������
    TALIASADDR& GetACFAlias( u8 byAliasNo )
    {
        if ( byAliasNo < MAXALIASNUM ) 
            return m_atDestAlias[byAliasNo];
        else
            return m_atDestAlias[0];
    }
}TACFINFO, *PTACFINFO;

//DRQ
typedef struct tagDRQInfo
{
	TALIASADDR		m_tEndpointID;			    //�ն�ID,GK��
	s8  			m_achConferenceID[LEN_GUID];//����ID,GK��
	s32				m_nCRV;					    //���вο�ֵ,GK��
	cmRASDisengageReason m_eReason;			    //DRQ��ԭ��		
	s8  			m_achCallID[LEN_GUID];	    //����ID,GK��
	TALIASADDR		m_tGKID;				    //GK ID,GK��				(optional)
	BOOL			m_bAnsweredCall;		    //�Ƿ�Ϊ���ж�,GK��

	TNETADDR		m_tDestAddr;			    //DRQ�Ľ��ܶ˵�ַ
	
	tagDRQInfo()
	{
		Clear();
	}

	void Clear()
	{
		memset(&m_tEndpointID,0,sizeof(TALIASADDR));
		memset(m_achConferenceID,0,sizeof(m_achConferenceID));
		memset(m_achCallID,0,sizeof(m_achCallID));
		memset(&m_tGKID,0,sizeof(TALIASADDR));
		m_tDestAddr.Clear();
		m_bAnsweredCall = FALSE;
		m_eReason = (cmRASDisengageReason)0;
		m_nCRV = 0;
		m_tDestAddr.SetNetAddress( 0, RASPORT );
	}

    //�����ն�ID
    void SetEndpointID( TALIASADDR &tEndpointID )
    {
        m_tEndpointID = tEndpointID;
    }
    //�õ��ն�ID
    TALIASADDR& GetEndpointID()
    {
        return m_tEndpointID;
    }

    //���û���ID
    void SetConferenceID( s8 *pchConferenceID, u8 byLen )
    {
        if ( pchConferenceID == NULL )
            return;
        
        memset( m_achConferenceID, 0, sizeof(m_achConferenceID) );
        u8 byRealLen = min( byLen, LEN_GUID );
        strncpy( m_achConferenceID, pchConferenceID, byRealLen );
        m_achConferenceID[byRealLen] = '\0';
    }
    //�õ�����ID
    s8* GetConferenceID()
    {
        return m_achConferenceID;
    }

    //���ú��вο�ֵ
    void SetCRV( s32 nCRV )
    {
        m_nCRV = nCRV;
    }
    //�õ����вο�ֵ
    s32 GetCRV()
    {
        return m_nCRV;
    }

    //����DRQ��ԭ��
    void SetDRQReason( cmRASDisengageReason emDRQReason )
    {
        m_eReason = emDRQReason;
    }
    //�õ�DRQ��ԭ��
    cmRASDisengageReason GetDRQReason()
    { 
        return m_eReason;
    }

    //���ú���ID
    void SetCallID( s8 *pchCallID, u8 byLen )
    {
        if ( pchCallID == NULL )
            return;
        
        memset( m_achCallID, 0, sizeof(m_achCallID) );
        u8 byRealLen = min( byLen, LEN_GUID );
        strncpy( m_achCallID, pchCallID, byRealLen );
        m_achCallID[byRealLen] = '\0';
    }
    //�õ�����ID
    s8* GetCallID()
    {
        return m_achCallID;
    }
    
    //����GK ID
    void SetGKID( TALIASADDR &tGKID )
    {
        m_tGKID = tGKID;
    }
    //�õ�GK ID
    TALIASADDR& GetGKID()
    {
        return m_tGKID;
    }

    //�����Ƿ񱻽�
    void SetAnsweredCall( BOOL bAnsweredCall )
    {
        m_bAnsweredCall = bAnsweredCall;
    }
    //�ж��Ƿ񱻽�
    BOOL IsAnsweredCall()
    {
        return m_bAnsweredCall;
    }
    
    //����DRQ�Ľ��ܶ˵�ַ
    void SetDestAddr( TNETADDR &tDestAddr )
    {
        m_tDestAddr = tDestAddr;
    }
    //�õ�DRQ�Ľ��ܶ˵�ַ
    TNETADDR& GetDestAddr()
    {
        return m_tDestAddr;
    }
}TDRQINFO, *PTDRQINFO;

//URQ
typedef struct tagURQInfo
{
	TNETADDR		m_tCallAddr;			//Դ�˺��������ַ
	TALIASADDR		m_atAlias[MAXALIASNUM];	//��GKע��ʱ�Ķ������		(optional)
	TALIASADDR		m_tEndpointID;			//�ն�ID					(optional)
	TALIASADDR		m_tGKID;				//GK ID						(optional)
	cmRASUnregReason m_eReason;				//URQ��ԭ��					(optional)
	
	TNETADDR		m_tDestAddr;			//URQ�Ľ��ܶ˵�ַ
	
	tagURQInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_tCallAddr.Clear();		
		memset(m_atAlias,0,sizeof(m_atAlias));		
		memset(&m_tEndpointID,0,sizeof(TALIASADDR));	
		memset(&m_tGKID,0,sizeof(TALIASADDR));
		m_tDestAddr.Clear();
		m_eReason = cmRASUnregReasonUndefinedReason;
		m_tCallAddr.SetNetAddress( 0, CALLPORT );
		m_tDestAddr.SetNetAddress( 0, RASPORT );
	}

    //����Դ�˺��������ַ
    void SetCallAddr( TNETADDR &tCallAddr )
    {
        m_tCallAddr = tCallAddr;
    }
    //�õ�Դ�˺��������ַ
    TNETADDR& GetCallAddr()
    {
        return m_tCallAddr;
    }

    //������GKע��ʱ�Ķ������
    void SetURQAlias( TALIASADDR &tAlias, u8 byAliasNo )
    {
        if ( byAliasNo >= MAXALIASNUM )
            return;
        
        m_atAlias[byAliasNo] = tAlias;
    }
    //�õ���GKע��ʱ�Ķ������
    TALIASADDR& GetURQAlias( u8 byAliasNo )
    {
        if ( byAliasNo < MAXALIASNUM ) 
            return m_atAlias[byAliasNo];
        else
            return m_atAlias[0];
    }

    //�����ն�ID
    void SetEndpointID( TALIASADDR &tEndpointID )
    {
        m_tEndpointID = tEndpointID;
    }
    //�õ��ն�ID
    TALIASADDR& GetEndpointID()
    {
        return m_tEndpointID;
    }

    //����GK ID
    void SetGKID( TALIASADDR &tGKID )
    {
        m_tGKID = tGKID;
    }
    //�õ�GK ID
    TALIASADDR& GetGKID()
    {
        return m_tGKID;
    }

    //����URQ��ԭ��
    void SetURQReason( cmRASUnregReason emURQReason )
    {
        m_eReason = emURQReason;
    }
    //�õ�URQ��ԭ��
    cmRASUnregReason GetURQReason()
    { 
        return m_eReason;
    }

    //����URQ�Ľ��ܶ˵�ַ
    void SetDestAddr( TNETADDR &tDestAddr )
    {
        m_tDestAddr = tDestAddr;
    }
    //�õ�URQ�Ľ��ܶ˵�ַ
    TNETADDR& GetDestAddr()
    {
        return m_tDestAddr;
    }
}TURQINFO, *PTURQINFO;

//BRQ
typedef struct tagBRQInfo
{
	TALIASADDR		m_tEndpointID;			    //�ն�ID,GK��
	s8			    m_achConferenceID[LEN_GUID];//����ID,GK��
	s32				m_nCRV;					    //���вο�ֵ,GK��
	cmCallType		m_eCallType;			    //��������,GK�ã�Ĭ��Ϊ��Ե�	(optional)
	s32				m_nBandWidth;			    //��λ��kbps
	
	s8			    m_achCallID[LEN_GUID];	    //����ID,GK��
	TALIASADDR		m_tGKID;				    //GK ID,GK��					(optional)
	BOOL			m_bAnsweredCall;		    //�Ƿ�Ϊ���ж�,GK��

	TNETADDR		m_tDestAddr;			    //BRQ�Ľ��ܶ˵�ַ
	
	tagBRQInfo()
	{
		Clear();
	}

	void Clear()
	{
		memset(&m_tEndpointID,0,sizeof(TALIASADDR));
		memset(&m_achConferenceID,0,sizeof(m_achConferenceID));
		memset(&m_achCallID,0,sizeof(m_achCallID));
		memset(&m_tGKID,0,sizeof(TALIASADDR));
		m_tDestAddr.Clear();
		m_eCallType = cmCallTypeP2P;
		m_tDestAddr.SetNetAddress( 0, RASPORT );
		m_nBandWidth = 0;
		m_nCRV = 0;
		m_bAnsweredCall = FALSE;
	}

    //�����ն�ID
    void SetEndpointID( TALIASADDR &tEndpointID )
    {
        m_tEndpointID = tEndpointID;
    }
    //�õ��ն�ID
    TALIASADDR& GetEndpointID()
    {
        return m_tEndpointID;
    }

    //���û���ID
    void SetConferenceID( s8 *pchConferenceID, u8 byLen )
    {
        if ( pchConferenceID == NULL )
            return;
        
        memset( m_achConferenceID, 0, sizeof(m_achConferenceID) );
        u8 byRealLen = min( byLen, LEN_GUID );
        strncpy( m_achConferenceID, pchConferenceID, byRealLen );
        m_achConferenceID[byRealLen] = '\0';
    }
    //�õ�����ID
    s8* GetConferenceID()
    {
        return m_achConferenceID;
    }

    //���ú��вο�ֵ
    void SetCRV( s32 nCRV )
    {
        m_nCRV = nCRV;
    }
    //�õ����вο�ֵ
    s32 GetCRV()
    {
        return m_nCRV;
    }

    //���ú�������
    void SetCallType( cmCallType emCallType )
    {
        m_eCallType = emCallType;
    }
    //�õ���������
    cmCallType GetCallType()
    { 
        return m_eCallType;
    }

    //���ô���
    void SetBandWidth( s32 nBandWidth )
    {
        m_nBandWidth = nBandWidth;
    }
    //�õ�����
    s32 GetBandWidth()
    {
        return m_nBandWidth;
    }

    //���ú���ID
    void SetCallID( s8 *pchCallID, u8 byLen )
    {
        if ( pchCallID == NULL )
            return;
        
        memset( m_achCallID, 0, sizeof(m_achCallID) );
        u8 byRealLen = min( byLen, LEN_GUID );
        strncpy( m_achCallID, pchCallID, byRealLen );
        m_achCallID[byRealLen] = '\0';
    }
    //�õ�����ID
    s8* GetCallID()
    {
        return m_achCallID;
    }

    //����GK ID
    void SetGKID( TALIASADDR &tGKID )
    {
        m_tGKID = tGKID;
    }
    //�õ�GK ID
    TALIASADDR& GetGKID()
    {
        return m_tGKID;
    }

    //�����Ƿ񱻽�
    void SetAnsweredCall( BOOL bAnsweredCall )
    {
        m_bAnsweredCall = bAnsweredCall;
    }
    //�ж��Ƿ񱻽�
    BOOL IsAnsweredCall()
    {
        return m_bAnsweredCall;
    }

    //����BRQ�Ľ��ܶ˵�ַ
    void SetDestAddr( TNETADDR &tDestAddr )
    {
        m_tDestAddr = tDestAddr;
    }
    //�õ�BRQ�Ľ��ܶ˵�ַ
    TNETADDR& GetDestAddr()
    {
        return m_tDestAddr;
    }
}TBRQINFO, *PTBRQINFO;

//BCF
typedef struct tagBCFInfo
{
	s32				m_nBandWidth;			//��λ��kbps
	tagBCFInfo()
	{
		m_nBandWidth = 0;
	}

    //���ô���
    void SetBandWidth( s32 nBandWidth )
    {
        m_nBandWidth = nBandWidth;
    }
    //�õ�����
    s32 GetBandWidth()
    {
        return m_nBandWidth;
    }
}TBCFINFO, *PTBCFINFO;

//LRQ
typedef struct tagLRQInfo
{
	TALIASADDR		m_tEndpointID;			//�ն�ID,GK��		(optional)
	TALIASADDR		m_tDestAlias;			//Ŀ�Ķ˱���
	TNETADDR		m_tReplyAddr;			//���Ͷ˵�ַ	
	TALIASADDR		m_tGKID;				//GK ID,GK��		(optional)

	TNETADDR		m_tResponseAddr;		//���ܶ˵�ַ

	tagLRQInfo()
	{
		Clear();
	}

	void Clear()
	{
		memset(&m_tEndpointID,0,sizeof(TALIASADDR));	
		memset(&m_tDestAlias,0,sizeof(TALIASADDR));			
		m_tReplyAddr.Clear();
		memset(&m_tGKID,0,sizeof(TALIASADDR));
		m_tResponseAddr.Clear();
		m_tReplyAddr.SetNetAddress( 0, RASPORT );
		m_tResponseAddr.SetNetAddress( 0, RASPORT );
	}

    //�����ն�ID
    void SetEndpointID( TALIASADDR &tEndpointID )
    {
        m_tEndpointID = tEndpointID;
    }
    //�õ��ն�ID
    TALIASADDR& GetEndpointID()
    {
        return m_tEndpointID;
    }

    //����Ŀ�Ķ˱���
    void SetDestAlias( TALIASADDR &tDestAlias )
    {
        m_tDestAlias = tDestAlias;
    }
    //�õ�Ŀ�Ķ˱���
    TALIASADDR& GetDestAlias()
    {
        return m_tDestAlias;
    }

    //���÷��Ͷ˵�ַ
    void SetReplyAddr( TNETADDR &tReplyAddr )
    {
        m_tReplyAddr = tReplyAddr;
    }
    //�õ����Ͷ˵�ַ
    TNETADDR& GetReplyAddr()
    {
        return m_tReplyAddr;
    }
    
    //����GK ID
    void SetGKID( TALIASADDR &tGKID )
    {
        m_tGKID = tGKID;
    }
    //�õ�GK ID
    TALIASADDR& GetGKID()
    {
        return m_tGKID;
    }

    //���ý��ܶ˵�ַ
    void SetResponseAddr( TNETADDR &tResponseAddr )
    {
        m_tResponseAddr = tResponseAddr;
    }
    //�õ����ܶ˵�ַ
    TNETADDR& GetResponseAddr()
    {
        return m_tResponseAddr;
    }
}TLRQINFO, *PTLRQINFO;

//LCF
typedef struct tagLCFInfo
{
	TNETADDR		m_tCallAddr;			//���������ַ
	TNETADDR		m_tRASAddr;				//RAS��ַ
	cmEndpointType	m_nDestinationType;		//�ն�����			(optional)

	tagLCFInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_tCallAddr.Clear();		
		m_tRASAddr.Clear();
		m_tCallAddr.SetNetAddress( 0, CALLPORT );
		m_tRASAddr.SetNetAddress( 0, RASPORT );
		m_nDestinationType = cmEndpointTypeTerminal;
	}

    //���ú��������ַ
    void SetCallAddr( TNETADDR &tCallAddr )
    {
        m_tCallAddr = tCallAddr;
    }
    //�õ����������ַ
    TNETADDR& GetCallAddr()
    {
        return m_tCallAddr;
    }
    
    //����RAS��ַ
    void SetRASAddr( TNETADDR &tRASAddr )
    {
        m_tRASAddr = tRASAddr;
    }
    //�õ�RAS��ַ
    TNETADDR& GetRASAddr()
    {
        return m_tRASAddr;
    }
    
    //�����ն�����
    void SetDestinationType( cmEndpointType emDestinationType )
    {
        m_nDestinationType = emDestinationType;
    }
    //�õ��ն�����
    cmEndpointType GetDestinationType()
    {
        return m_nDestinationType;
    }
}TLCFINFO, *PTLCFINFO;

//IRQ
typedef struct tagIRQInfo
{	
	s32				m_nCRV;					//���вο�ֵ
	s8  			m_achCallID[LEN_GUID];	//����ID

	HCALL			m_hsCall;				//���о��	
	TNETADDR		m_tPeerRasAddr;			//�Զ�RAS��ַ

	tagIRQInfo()
	{
		Clear();
	}

	void Clear()
	{
		memset( m_achCallID, 0, sizeof(m_achCallID));
		m_tPeerRasAddr.Clear();
		m_nCRV = 0;
		m_hsCall = NULL;
		m_tPeerRasAddr.SetNetAddress( 0, RASPORT );
	}

    //���ú��вο�ֵ
    void SetCRV( s32 nCRV )
    {
        m_nCRV = nCRV;
    }
    //�õ����вο�ֵ
    s32 GetCRV()
    {
        return m_nCRV;
    }

    //���ú���ID
    void SetCallID( s8 *pchCallID, u8 byLen )
    {
        if ( pchCallID == NULL )
            return;
        
        memset( m_achCallID, 0, sizeof(m_achCallID) );
        u8 byRealLen = min( byLen, LEN_GUID );
        strncpy( m_achCallID, pchCallID, byRealLen );
        m_achCallID[byRealLen] = '\0';
    }
    //�õ�����ID
    s8* GetCallID()
    {
        return m_achCallID;
    }

    //���ú��о��
    void SetHCALL( HCALL hsCall )
    {
        if ( hsCall != NULL )
            m_hsCall = hsCall;
    }
    //�õ����о��
    HCALL GetHCALL()
    {
        return m_hsCall;
    }

    //���öԶ�RAS��ַ
    void SetPeerRasAddr( TNETADDR &tPeerRasAddr )
    {
        m_tPeerRasAddr = tPeerRasAddr;
    }
    //�õ��Զ�RAS��ַ
    TNETADDR& GetPeerRasAddr()
    {
        return m_tPeerRasAddr;
    }
}TIRQINFO, *PTIRQINFO;

//IRR
typedef struct tagIRRInfo
{
	cmEndpointType	m_eEndpointType;		    //�ն�����,GK��
	TALIASADDR		m_tEndpointID;			    //�ն�ID,GK��
	TNETADDR		m_tRASAddr;				    //����RAS��ַ
	TNETADDR		m_tCallAddr;			    //���������ַ
	TALIASADDR		m_atAlias[MAXALIASNUM];	    //��GKע��Ķ������	(optional)	
	//perCallInfo
	s32				m_nCRV;					    //���вο�ֵ,GK��
	s8				m_achConferenceID[LEN_GUID];//����ID,GK��
	BOOL			m_bOriginator;			    //�Ƿ�Ϊ����,GK��

	s8				m_achCallID[LEN_GUID];	    //����ID,GK��
	BOOL			m_bNeedResponse;		    //�Ƿ���ӦIRR��Ϣ
	BOOL			m_bIsUnsolicited;		    //Ĭ��ΪTRUE��������IRR��FALSE����ӦIRQ
											
	TNETADDR		m_tGKAddr;				    //GK��ַ
	

	tagIRRInfo()
	{
		Clear();
	}

	void Clear()
	{
		memset(&m_tEndpointID,0,sizeof(TALIASADDR));	
		m_tRASAddr.Clear();			
		m_tCallAddr.Clear();		
		memset(m_atAlias,0,sizeof(m_atAlias));
		m_tGKAddr.Clear();			
		
		m_bNeedResponse  = FALSE;
		m_bIsUnsolicited = TRUE;
		m_tRASAddr.SetNetAddress( 0, RASPORT );
		m_tCallAddr.SetNetAddress( 0, CALLPORT );
		m_tGKAddr.SetNetAddress( 0, RASPORT );
	}

    //�����ն�����
    void SetEndpointType( cmEndpointType emEndpointType )
    {
        m_eEndpointType = emEndpointType;
    }
    //�õ��ն�����
    cmEndpointType GetEndpointType()
    {
        return m_eEndpointType;
    }

    //�����ն�ID
    void SetEndpointID( TALIASADDR &tEndpointID )
    {
        m_tEndpointID = tEndpointID;
    }
    //�õ��ն�ID
    TALIASADDR& GetEndpointID()
    {
        return m_tEndpointID;
    }

    //����RAS��ַ
    void SetRASAddr( TNETADDR &tRASAddr )
    {
        m_tRASAddr = tRASAddr;
    }
    //�õ�RAS��ַ
    TNETADDR& GetRASAddr()
    {
        return m_tRASAddr;
    }

    //���ú��������ַ
    void SetCallAddr( TNETADDR &tCallAddr )
    {
        m_tCallAddr = tCallAddr;
    }
    //�õ����������ַ
    TNETADDR& GetCallAddr()
    {
        return m_tCallAddr;
    }

    //����ע�����
    void SetIRRAlias( TALIASADDR &tAlias, u8 byAliasNo )
    {
        if ( byAliasNo >= MAXALIASNUM )
            return;
        
        m_atAlias[byAliasNo] = tAlias;
    }
    //�õ�ע��ı���
    TALIASADDR& GetIRRAlias( u8 byAliasNo )
    {
        if ( byAliasNo < MAXALIASNUM ) 
            return m_atAlias[byAliasNo];
        else
            return m_atAlias[0];
    }

    //���ú��вο�ֵ
    void SetCRV( s32 nCRV )
    {
        m_nCRV = nCRV;
    }
    //�õ����вο�ֵ
    s32 GetCRV()
    {
        return m_nCRV;
    }

    //���û���ID
    void SetConferenceID( s8 *pchConferenceID, u8 byLen )
    {
        if ( pchConferenceID == NULL )
            return;
        
        memset( m_achConferenceID, 0, sizeof(m_achConferenceID) );
        u8 byRealLen = min( byLen, LEN_GUID );
        strncpy( m_achConferenceID, pchConferenceID, byRealLen );
        m_achConferenceID[byRealLen] = '\0';
    }
    //�õ�����ID
    s8* GetConferenceID()
    {
        return m_achConferenceID;
    }
    
    //�����Ƿ�����
    void SetOriginator( BOOL bOriginator )
    {
        m_bOriginator = bOriginator;
    }
    //�ж��Ƿ�����
    BOOL IsOriginator()
    {
        return m_bOriginator;
    }

    //���ú���ID
    void SetCallID( s8 *pchCallID, u8 byLen )
    {
        if ( pchCallID == NULL )
            return;
        
        memset( m_achCallID, 0, sizeof(m_achCallID) );
        u8 byRealLen = min( byLen, LEN_GUID );
        strncpy( m_achCallID, pchCallID, byRealLen );
        m_achCallID[byRealLen] = '\0';
    }
    //�õ�����ID
    s8* GetCallID()
    {
        return m_achCallID;
    }
    
    //�����Ƿ���ӦIRR��Ϣ
    void SetNeedResponse( BOOL bNeedResponse )
    {
        m_bNeedResponse = bNeedResponse;
    }
    //�ж��Ƿ���ӦIRR��Ϣ
    BOOL IsNeedResponse()
    {
        return m_bNeedResponse;
    }

    //�����Ƿ�Unsolicited��Ϣ
    void SetUnsolicited( BOOL bIsUnsolicited )
    {
        m_bIsUnsolicited = bIsUnsolicited;
    }
    //�ж��Ƿ�Unsolicited��Ϣ
    BOOL IsUnsolicited()
    {
        return m_bIsUnsolicited;
    }
    
    //����GK��ַ
    void SetGKAddr( TNETADDR &tGkAddr )
    {
        m_tGKAddr = tGkAddr;
    }
    //�õ�GK��ַ
    TNETADDR& GetGKAddr()
    {
        return m_tGKAddr;
    }
    
}TIRRINFO, *PTIRRINFO;

//GRQ
typedef struct tagGRQInfo
{	
	TNETADDR		m_tRASAddr;				    //�ն�RAS��ַ
	cmEndpointType	m_eEndpointType;		    //�ն�����
	TALIASADDR		m_tGKID;				    //GK ID,GK��

	tagGRQInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_tRASAddr.Clear();			
		memset(&m_tGKID,0,sizeof(TALIASADDR));	
		m_tRASAddr.SetNetAddress( 0, RASPORT );
		m_eEndpointType = cmEndpointTypeTerminal;
	}
}TGRQINFO, *PTGRQINFO;

//GCF
typedef struct tagGCFInfo
{	
	TALIASADDR		m_tGKID;				    //GK ID,GK��
	TNETADDR		m_tRASAddr;				    //GK��RAS��ַ

	tagGCFInfo()
	{
		Clear();
	}

	void Clear()
	{
		memset(&m_tGKID,0,sizeof(TALIASADDR));	
		m_tRASAddr.Clear();		
		m_tRASAddr.SetNetAddress( 0, RASPORT );
	}
}TGCFINFO, *PTGCFINFO;

//add by daiqing 20100720 for 460
//ServiceControlSession
typedef struct tagServiceControlSession
{
	u8       m_bySessionId;
    u8       m_byReason;
}TServiceControlSession, *PTServiceControlSession;

//SCI
typedef struct tagSCIInfo
{
	TServiceControlSession m_tServiceControlSession;
    TNETADDR        m_tCallSignallingAddress;   //������е�ַ
	u8	            m_abyCallId[LEN_GUID];      //CallIdentifier
	
	tagSCIInfo()
	{
		Clear();
	}
	
	void Clear()
	{
		memset(&m_tServiceControlSession, 0, sizeof(m_tServiceControlSession));
		m_tCallSignallingAddress.Clear();
		memset(m_abyCallId, 0, LEN_GUID);
	}
	
}TSCIINFO, *PTSCIINFO;
//end


//SCR
typedef struct tagSCRINFO
{
	u16             m_wRequestSeqNum;           //�������б��
	TALIASADDR      m_tEndpointID;
	s8	            m_abyCallId[LEN_GUID];      //CallIdentifier
}TSCRINFO;

//H323 Annex Q
typedef struct
{
	u8 m_byAction;			  //start, continue, stop, video source, preset
	
	union 
	{
		u8 m_byRequest;		  //for PTFZ operations
		u8 m_bySourceNo;      //for VIDEO SOURCE operations
		u8 m_byPresetNo;      //for PRESET operations
	}arguments;
	
	u8 m_byTimeout;			  //for start action only ,unit 50ms, 0��ʾ800ms	
}TFeccStruct, *PTFeccStruct;

typedef struct 
{
	TFeccStruct m_tFeccStruct;
	TTERLABEL   m_tSrcTer;
	TTERLABEL   m_tDstTer;
}TH245Fecc;

//H239 Information
typedef struct tagH239Info
{
    emH239InfoType  m_emH239InfoType;
    TTERLABEL       m_tTerLabel;
    s32             m_nChannelId;
    
    /*��emH239FlowControlReleaseResponse
      ��emH239PresentationTokenResponse��ʹ��
      TRUE��ʾͬ�⣬FALSE��ʾ�ܾ�*/
    BOOL            m_bIsResponseAck;   
    
    /*ͨ�����ʣ���λ��100bit/s����Χ��1��19200
      ��emH239FlowControlReleaseRequest
      ��emH239FlowControlReleaseResponse��Ϣ��ʹ��      
    */
    u32             m_dwBitRate;          
    
    /*
      MTȡ1��127֮������ֵ;
      MCU������Ϊ0�������о��庬��
    */
    u8              m_bySymmetryBreaking; 
    
    tagH239Info()
    {
        Clear();
    }

    void Clear()
    {
        m_emH239InfoType     = emH239InfoTypeInvalid;
        m_bIsResponseAck     = FALSE;
        
        m_dwBitRate          = 0;
        m_bySymmetryBreaking = 0;
        m_nChannelId         = 0;
        
        m_tTerLabel.Clear();
    }

    void host2net(BOOL bhton)
    {
        s32 nH239InfoType = m_emH239InfoType;
        if (bhton)
        {
            m_emH239InfoType = (emH239InfoType)htonl(nH239InfoType);
            m_nChannelId     = htonl(m_nChannelId);
            m_bIsResponseAck = htonl(m_bIsResponseAck);
            m_dwBitRate      = htonl(m_dwBitRate);
        }
        else
        {
            m_emH239InfoType = (emH239InfoType)ntohl(nH239InfoType);
            m_nChannelId     = ntohl(m_nChannelId);
            m_bIsResponseAck = ntohl(m_bIsResponseAck);
            m_dwBitRate      = ntohl(m_dwBitRate);
        }
    }

    BOOL SetH239InfoType(emH239InfoType nH239InfoType)
    {
        if (nH239InfoType>emH239InfoTypeInvalid
            && nH239InfoType<emH239InfoTypeEnd)
        {
            m_emH239InfoType = nH239InfoType;
            return TRUE;
        }
        return FALSE;
    }
    emH239InfoType GetH239InfoType()
    {
        return m_emH239InfoType;
    }
    
    void SetTerLabel(TTERLABEL &tTerlabel)
    {
        m_tTerLabel = tTerlabel;
    }

    TTERLABEL &GetTerlabel()
    {
        return m_tTerLabel;
    }


    void SetSymmetryBreaking(u8 bySymmetryBreaking)
    {
        m_bySymmetryBreaking = bySymmetryBreaking;
    }
    u8 GetSymmetryBreaking()
    {
        return m_bySymmetryBreaking;
    }
    
    void SetResponseAck(BOOL bIsResponseAck)
    {
        m_bIsResponseAck = bIsResponseAck;
    }
    BOOL IsResponseAck()
    {
        return m_bIsResponseAck;
    }
    
    void SetChannelId(HCHAN hsChan)
    {
        m_nChannelId = cmGetLCNFromHchan(hsChan);
    }
    s32 GetChannelId()
    {
        return m_nChannelId;
    }
    void SetChannelId(s32 nChannelId)
    {
        m_nChannelId = nChannelId;
    }
    
}TH239INFO,*PTH239INFO;
//add by zhanghb 100316 
//�޸����kdvpts����һ��
//#define KDV_NSM_MAX_LEN        (s32)1300  //��ʱ1300�ֽ�
#define KDV_NSM_MAX_LEN        (s32)(1024*10)  //��ʱ1300�ֽ�
//�Ǳ���Ϣ�����
#define KDVP_NSM_SUCCESS          (u32)0
#define KDVP_NSM_SER_DB_ERR       (u32)1

//�Ǳ���Ϣ�Ŷ���
//add by yj for QUERY [20121212]
// #define KDVP_NSM_START_ID         (u32)0
// #define KDVP_NSM_GETMTLIST_REQ    (u32)(KDVP_NSM_START_ID + 1) //MT ��GK���������ն��б�
// #define KDVP_NSM_GETMTLIST_RSP    (u32)(KDVP_NSM_START_ID + 2) //�ظ�
typedef enum
{
	KDVP_NSM_START_ID		= 0,
	KDVP_NSM_GETMTLIST_REQ,									//MT ��GK���������ն��б�
	KDVP_NSM_GETMTLIST_RSP,									//����ƽ̨�ظ�KDVP_NSM_GETMTLIST_REQ

	KDVP_NSM_NEW_BEGIN		= (KDVP_NSM_START_ID + 10),
	KDVP_NSM_PALTFORMCAP_NOTIFY,							//GK��֪h323ʵ��ƽ̨����
	KDVP_NSM_GETMTLIST_RSP2,								//����ƽ̨�ظ�KDVP_NSM_GETMTLIST_REQ
	KDVP_NSM_GETMTLIST_REJECT,								//4.2GK�ظ�KDVP_NSM_GETMTLIST_REQ
	
	//MT��GK�����ַ����Ϣ
	KDVP_NSM_ADDRBOOK_ENTRY_REQ,
	KDVP_NSM_ADDRBOOK_ENTRY_REJECT,
	KDVP_NSM_ADDRBOOK_ENTRY_RSP,
	
	KDVP_NSM_ADDRBOOK_GROUP_REQ,
	KDVP_NSM_ADDRBOOK_GROUP_REJECT,
	KDVP_NSM_ADDRBOOK_GROUP_RSP,
	
	KDVP_NSM_ADDRBOOK_GROUPLEVEL_REQ,
	KDVP_NSM_ADDRBOOK_GROUPLEVEL_REJECT,
	KDVP_NSM_ADDRBOOK_GROUPLEVEL_RSP,
	
	//�ն�ע�� MT<-- >MTCarrier
	KDVP_NSM__REG_REQ,										
	KDVP_NSM_REG_ACK,
	KDVP_NSM_REG_NACK,
	KDVP_NSM__ROUNDTRIP_TIMER,
	
	//0.1 ����¼�� MT<-->GK
	KDVP_NSM_STARTP2PREC_REQ,
	KDVP_NSM_STARTP2PREC_REJECT,
	KDVP_NSM_STARTP2PREC_RSP,
	
	//0.2 ��ֹ¼�� ˫���
	KDVP_NSM_STOPP2PREC_CMD,
	KDVP_NSM_P2PRECSTATUS_NTY,
	KDVP_NSM_P2PFASTUPDATE_CMD,
	KDVP_NSM_P2P_COMMON_MSG,

	KDVP_NSM_END_ID           =200,
}emKDVPNsmType;
//end [20121212]
  
#ifdef WIN32
#pragma comment( lib, "ws2_32.lib" ) 
#pragma pack( push )
#pragma pack( 1 )
#define window( x )	x
#define PACKED 
#else
#include <netinet/in.h>
#define window( x )
#define PACKED __attribute__((__packed__))	// ȡ�����������Ż�����
#endif

typedef struct tagNSMInfo
{
	u32          m_dwNSMID;               //��Ϣ��
    u32          m_dwErrorCode;           //������ �ظ���Ϣʱ������
    u32          m_dwSequenceNumber;      //���к� ��ʱδ��
    u32          m_dwContentLen;          //��Ϣ�����ݳ���
    u32          m_dwStructNum;           //��Ϣ��Ľṹ����Ŀ
    BOOL         m_bWillContinue;         //�Ƿ��к�������Ϣ��������Ϣ�峤��̫�������
	TALIASADDR   m_tMTAlias;              //�ն˱���Ŀǰֻ��E164��
	u8           m_bybuf[KDV_NSM_MAX_LEN];//��Ϣ��

    tagNSMInfo()
    {
        Clear();
    }
	
    void Clear()
    {
        m_dwNSMID            = 0;
        m_dwErrorCode        = KDVP_NSM_SUCCESS;       
        m_dwSequenceNumber   = 0;
        m_dwContentLen       = 0;
        m_dwStructNum        = 0;
		m_bWillContinue      = FALSE;
        
        memset(m_bybuf,0,KDV_NSM_MAX_LEN);
    }
	//���ñ���
	void SetAliasAddr( TALIASADDR tAliasAddr )
	{		
		m_tMTAlias.SetAliasAddr(tAliasAddr.GetAliasType(),tAliasAddr.GetAliasName());
		m_tMTAlias.m_emType = (AliasType)htonl(tAliasAddr.m_emType);
	}
	//��ȡ��������
    void GetAliasAddr( TALIASADDR &tAliasAddr)
	{
		tAliasAddr.m_emType = (AliasType)ntohl(m_tMTAlias.m_emType);
		tAliasAddr.SetAliasAddr(tAliasAddr.GetAliasType(),m_tMTAlias.GetAliasName());
	}
	void SetNSMID(u32 dwNSMID)
	{ 
		m_dwNSMID = htonl(dwNSMID);
	}
	u32 GetNSMID()
	{
		return ntohl(m_dwNSMID);
	}
	void SetErrorCode(u32 dwErrorCode)
	{
		m_dwErrorCode = htonl(dwErrorCode);
	}
	u32 GetErrorCode()
	{
		return ntohl(m_dwErrorCode);
	}
	void SetSQN(u32 dwSQN)
	{
		m_dwSequenceNumber = htonl(dwSQN);
	}
	u32 GetSQN()
	{
		return ntohl(m_dwSequenceNumber);
	}
	void SetStructNum(u32 dwMsgNum)
	{
		m_dwStructNum = htonl(dwMsgNum);
	}
	u32 GetStructNum()
	{
		return ntohl(m_dwStructNum);
	}
    void SetWillContinue(BOOL bWillContinue)
    {
        m_bWillContinue = htonl(bWillContinue);
    }
    BOOL IsWillContinue()
    {
        return ntohl(m_bWillContinue);
    }
    void SetContentLen(u32 dwContentLen)
    {
        m_dwContentLen = htonl(dwContentLen);
    }
    u32 GetContentLen()
    {
        return ntohl(m_dwContentLen);
    }
	u8* GetMsgData()
	{
		return (u8*)m_bybuf;
	}
	BOOL SetMsgData(u8 * pbuf,u32 dwMsgLen)
	{
		if (pbuf == NULL || dwMsgLen > KDV_NSM_MAX_LEN)
		{
			return FALSE;
		}
		//memcpy(m_bybuf,0, KDV_NSM_MAX_LEN);
		memset( m_bybuf, 0, KDV_NSM_MAX_LEN );
		memcpy(m_bybuf,pbuf,dwMsgLen);
		return TRUE;
	}
}
#if defined(_VXWORKS_) || defined(_LINUX_)
__attribute__ ( (packed) ) 
#endif // _VXWORKS_
TNSMInfo,*PTNSMInfo;

typedef struct tagNSM_MTList_RSP_BodyHead
{
private:
    cmEndpointType	m_emEndpointType;       //�ն�����
    TNETADDR        m_tRasAddr;             //RAS��ַ
    u16				m_wCallAddrNum;         //���������ַ�ĸ���    
    u16				m_wAliasNum;            //��������
    u32             m_dwAliasBufLen;        //ѹ����ı���buf����
	
public:
	
    void SetTerminalType( cmEndpointType emEndpointType )
    {
        m_emEndpointType = (cmEndpointType)htonl(emEndpointType);
    }
    cmEndpointType GetTerminalType()
    {
        return (cmEndpointType)ntohl(m_emEndpointType);
    }
	
    void SetAliasNum( u16 wAliasNum )
    {
        m_wAliasNum = htons(wAliasNum);
    }
    u16 GetAliasNum()
    {
        return ntohs(m_wAliasNum);
    }
    
    void SetAliasBufLen( u32 dwAliasBufLen )
    {
        m_dwAliasBufLen = htonl(dwAliasBufLen);
    }
    u32 GetAliasBufLen()
    {
        return ntohl(m_dwAliasBufLen);
    }
	
    void SetRASAddr( TNETADDR &tRASAddr )
    {
        m_tRasAddr = tRASAddr;
    }
    TNETADDR* GetRASAddr()
    {
        return &m_tRasAddr;
    }
	
    void SetCallAddrNum( u16 wCallAddrNum )
    {
        m_wCallAddrNum = htons(wCallAddrNum);
    }
    u16 GetCallAddrNum()
    {
        return ntohs(m_wCallAddrNum);
    }
}
#if defined(_VXWORKS_) || defined(_LINUX_)
__attribute__ ( (packed) ) 
#endif // _VXWORKS_
TNSM_MTList_RSP_BodyHead,*PTNSM_MTList_RSP_BodyHead;

#ifdef WIN32
#pragma pack( pop )
#endif

//�ָ������ṹ
BOOL NSM_DecodeAlias(IN u8 *pbyAliasBuf, IN u16 wAliasNum, IN u32 dwAliasBufLen, OUT TALIASADDR* atAlias, IN u16 wMaxAliasNum);
/***********************mmcu define**************************/

enum H323MCUMsgType
{
    CASCADE_MSGTYPE_BEGINNING,
        
        H_CASCADE_REGUNREG_REQ,   //[IN]&[OUT]:[TRegUnRegReq]	register request
        H_CASCADE_REGUNREG_RSP,   //[IN]&[OUT]:[TRegUnRegRsp]	register response
        
        H_CASCADE_NEWROSTER_NTF,  //[IN]&[OUT]:[TRosterList]  roster notify
        
        H_CASCADE_PARTLIST_REQ,   //[IN]&[OUT]:[TReq]         request part list 
        H_CASCADE_PARTLIST_RSP,   //[IN]&[OUT]:[TPartListRsp] reponse part list (dwpid ==0 ��ʾ�Է���MCU)
        
        H_CASCADE_INVITEPART_REQ, //[IN]&[OUT]:[TInvitePartReq]  invite part request
        H_CASCADE_INVITEPART_RSP, //[IN]&[OUT]:[Tsp]             invite part response
        H_CASCADE_NEWPART_NTF,    //[IN]&[OUT]:[TPart]           new part notify
        
        H_CASCADE_CALL_ALERTING_NTF, //[IN]&[OUT]:[TCallNtf]
        
        H_CASCADE_REINVITEPART_REQ, //[IN]&[OUT]:[TReInviteReq]    reinvite part request
        H_CASCADE_REINVITEPART_RSP, //[IN]&[OUT]:[Tsp]        reinvite part response
        
        H_CASCADE_DISCONNPART_REQ, //[IN]&[OUT]:[TPartReq]     disconnect part request
        H_CASCADE_DISCONNPART_RSP, //[IN]&[OUT]:[Tsp]         disconnect part response
        H_CASCADE_DISCONNPART_NTF, //[IN]&[OUT]:[TDiscPartNF] disconnect part notify
        
        
        H_CASCADE_DELETEPART_REQ, //[IN]&[OUT]:[TPartReq]		delete part request
        H_CASCADE_DELETEPART_RSP, //[IN]&[OUT]:[Tsp]			delete part response
        H_CASCADE_DELETEPART_NTF, //[IN]&[OUT]:[TPartNtf]   delete part notify (whether or not local)
        
        H_CASCADE_SETIN_REQ,      //[IN]&[OUT]:[TSetInReq]    request video in
        H_CASCADE_SETIN_RSP,      //[IN]&[OUT]:[Tsp]          response msg
        
        H_CASCADE_SETOUT_REQ,     //[IN]&[OUT]:[TSetOutReq]//��Ƶ������Լ�������(��Ƶ����:MCU->MT)
        H_CASCADE_SETOUT_RSP,     //[IN]&[OUT]:[Tsp]//��Ƶ������Լ���Ӧ��(��Ƶ����:MCU->MT)
        
        H_CASCADE_OUTPUT_NTF,     //[IN]&[OUT]:[TPartOutputNtf]      video output notify (dwpid ==0 ��ʾ�Է���MCU)
        
        H_CASCADE_NEWSPEAKER_NTF, //[IN]&[OUT]:[TNewSpeakerNtf]      newSpeaker output notify (dwpid ==0 ��ʾ�Է���MCU)
        
        H_CASCADE_AUDIOINFO_REQ,  //[IN]&[OUT]:[TConfVideInfoReq]         audio info request 
        H_CASCADE_AUDIOINFO_RSP,  //[IN]&[OUT]:[TConfAudioInfo]    audio info response
        
        H_CASCADE_VIDEOINFO_REQ,  //[IN]&[OUT]:[pReq]          conference videoinfo request 
        H_CASCADE_VIDEOINFO_RSP,  //[IN]&[OUT]:[TConfVideoInfo] conference videoinfo response
        
        
        H_CASCADE_CONFVIEW_CHG_NTF,//[IN]&[OUT]:[TConfViewChgNtf] conference view format(layout geometry)change notify
        
        H_CASCADE_PARTMEDIACHAN_REQ,   //[IN]&[OUT]:[TPartMediaChanReq] ��������Ա��/�ر���/��Ƶ/����ͨ��
        H_CASCADE_PARTMEDIACHAN_RSP,   //[IN]&[OUT]:[TRsp]    response
        H_CASCADE_PARTMEDIACHAN_NTF,   //[IN]&[OUT]:[TPartMediaChanNtf] �����Ա����/��Ƶ/����ͨ����/�رյ�֪ͨ

        H_CASCADE_GETMCUSERVICELIST_REQ, //[IN]&[OUT]:[TReq] ��ȡMCU�ϵķ���ģ���б��������Ϣ
		H_CASCADE_GETMCUSERVICELIST_RSP,//[IN]&[OUT]:[��ʱδ����]  response

		H_CASCADE_GETMUCCONFLIST_REQ,//[IN]&[OUT]:[TMCUConfListReq] ��ȡMCU�ϵ�ǰ�ٿ������л�����б�
		H_CASCADE_GETMUCCONFLIST_RSP,//[IN]&[OUT]:[��ʱδ����]
  
        H_CASCADE_GETCONFGIDBYNAME_REQ,//[IN]&[OUT]:[TGetConfIDByNameReq] ͨ���������ֻ�û���ID��������Ϣ
        H_CASCADE_GETCONFGIDBYNAME_RSP,//[IN]&[OUT]:[��ʱδ����]
		
        H_CASCADE_GET_CONFPROFILE_REQ,//[IN]&[OUT]:[TConfProfileReq] ��ȡMCU�ϵ�ǰ�ٿ������л����profile
		
        H_CASCADE_GET_CONFPROFILE_RSP,//[IN]&[OUT]:[��ʱδ����]

        H_CASCADE_NONSTANDARD_REQ,//[IN]&[OUT]:[TNonStandardReq] �Ǳ�(�Զ���)������Ϣ
        H_CASCADE_NONSTANDARD_RSP,//[IN]&[OUT]:[TNonStandardRsp] �Ǳ�(�Զ���)response��Ϣ
		H_CASCADE_NONSTANDARD_NTF,//[IN]&[OUT]:[TNonStandardMsg] �Ǳ�(�Զ���)notify��Ϣ
		//
        H_CASCADE_NOT_SUPPORTED,
		//Ŀǰ���ǻ���֧��,����radmuc֧�ֵ���Ϣ����
        H_CASCADE_VA_REQ,       //[IN]&[OUT]:[TVAReq]
        H_CASCADE_VA_RSP,       //[IN]&[OUT]:[TRsp]

        H_CASCADE_RELEASECONTROL_OF_CONF_REQ,//[IN]&[OUT]:[]
        H_CASCADE_RELEASECONTROL_OF_CONF_RSP,//[IN]&[OUT]:[]

        H_CASCADE_TAKECONTROL_OF_CONF_REQ,//[IN]&[OUT]:[]
        H_CASCADE_TAKECONTROL_OF_CONF_RSP,//[IN]&[OUT]:[]

        H_CASCADE_ALLPART_SETOUT_REQ,//[IN]&[OUT]:[]
        H_CASCADE_ALLPART_SETOUT_RSP,//[IN]&[OUT]:[]
        
        H_CASCADE_CREATE_CONF_REQ,//[IN]&[OUT]:[]
        H_CASCADE_CREATE_CONF_RSP,//[IN]&[OUT]:[]
        
        H_CASCADE_TERMINATE_CONF_REQ,//[IN]&[OUT]:[]
        H_CASCADE_TERMINATE_CONF_RSP,//[IN]&[OUT]:[]

        H_CASCADE_UNDEFINED_REQ,//[IN]&[OUT]:[]
        H_CASCADE_UNDEFINED_RSP,//[IN]&[OUT]:[]
        H_CASCADE_UNDEFINED_NTF,//[IN]&[OUT]:[]

        //add 2007.04.28
        H_CASCADE_SET_LAYOUT_AUTOSWITCH_REQUEST,//[IN]&[OUT]:TSetLayoutAutoswitchReq
        H_CASCADE_SET_LAYOUT_AUTOSWITCH_RESPONSE,
        
        CASCADE_MSGTYPE_ENDING
};

#ifndef H323CASCADE_H_

#define CASCADE_PORT		    (s32)3337
#define CASCADE_USERNAME_MAXLEN     (s32)32
#define CASCADE_USERPASS_MAXLEN     (s32)32 
#define CASCADE_NONSTANDARDMSG_MAXLEN (u32)1536
#define PART_NUM			     (s32)192//
#define STR_LEN                  (s32)16
#define CONFID_BYTELEN                   (s32)12// 
#define PID_POS                          (s32)4//
//#define MAX_VIEWS_PER_CONF               (s32)2
#define MAX_VIEWS_PER_CONF               (s32)4
#define MAX_GEOMETRYS_PER_VIEW           (s32)5
#define MAX_SUBFRAMES_PER_GEOMETRY       (s32)16
#define MAX_VIDEOSCHEMES_PER_VIEW        (s32)4
#define MAX_MIXERS_PER_CONF              (s32)16

#define MCU_PID                          (u32)0XFFFFFFFF
#define CACSCONF_ID                      (u32)0XFFFFFFFF
#define EMPTY_MT_PID                     (u32)0x0


#define E_TOO_MANY_ITEMS                 (s32)-1
#define E_ALREADY_EXISTED                (s32)-2
#define E_INVALID_PARAMETER              (s32)-3
#define E_NOT_EXISTED                    (s32)-4
#define E_SUBFRAMES_CONTRIBUTERS_UNMATCH (s32)-5
//#define S_RIGHT                             (s32)1
#define S_REPLACED                       (s32)2
#define S_RIGHT                          (s32)1

enum emConnState
{
	    emConnStateUnknown,                 //��MT,MCU������״̬δ֪����������δ
		emConnStateConnected,               //"connected"
		emConnStateDisconnected,            //"disconnected"
		emConnStateConnecting               //"alerting"
};

enum emEPType
{
    	emEPTypeUndefined,                  //��������
		emEPTypeMCU,                        //mcu,��������һ����ͨ�ն˵���ݲμӼ���������ǻ���
		emEPTypeTerminal,                   //��ͨ�ն�
		emEPTypeCascConf                    //mcu,���Ҳμ��˼�������
};



//time config struct
typedef struct tagTimeSpec
{
    s8 day;
    s8 hour;
    s8 minute;
    s8 second;
    s16 year;
    s8 month;
}TTimeSpec,*PTTimeSpec;

//��׼����ͷ,������������Ļ���
typedef struct tagRequest
{
    s32  m_nReqID;//��ˮ��/ϵ�к�
	s8   m_aszUserName[CASCADE_USERNAME_MAXLEN];//�ʺ�
	s8   m_aszUserPass[CASCADE_USERPASS_MAXLEN];//����
	//�����ʺź�����
	inline void SetUserNameAndPass(const s8 * aszUserName, const s8 *aszUserPass)
	{
		strncpy(m_aszUserName, aszUserName, CASCADE_USERNAME_MAXLEN-1);
		m_aszUserName[CASCADE_USERNAME_MAXLEN-1] = '\0';
		strncpy(m_aszUserPass, aszUserPass, CASCADE_USERPASS_MAXLEN-1);
		m_aszUserPass[CASCADE_USERPASS_MAXLEN-1] = '\0';
	}
}TReq;


//�Ǳ꼶����Ϣ�Ļ���
typedef struct tagNonStandardMsg
{
	s32 m_nMsgLen;//��Ϣ����
	u8	m_abyMsgBuf[CASCADE_NONSTANDARDMSG_MAXLEN];//��Ϣ��
}TNonStandardMsg;

//�Ǳ�(�Զ���)������Ϣ
typedef struct tagNonStandardReq: public TReq, public TNonStandardMsg{}TNonStandardReq;

//response��Ϣ�ķ���ֵ�ֶ�
enum emReturnValue
{
    emReturnValue_Ok = 0, //request��Ϣ�ѵõ���ȷ�Ĵ���
    emReturnValue_Error,//һ���Դ��󣬴���ԭ����
    emReturnValue_PartNotFound,//�������в�����������Ϣ��PIDָʾ�Ļ����Ա
    emReturnValue_ConfNotFound,//������Ϣ��confIDָ���Ļ����鲻����
    emReturnValue_ChannelNotFound,//�����Ա����Ƶ/��Ƶͨ��������
    emReturnValue_NoPermission,//�û���Ȩ�޲�����������Ϣ��������
    emReturnValue_XmlBadParams,//������Ϣ���ֶ��������ֶε�ֵ����/��Χ����
    emReturnValue_TimeOut,//������Ϣ����ʱ
    emReturnValue_NoResources,//mcuû���㹻����Դ������������Ϣ������Ƶ��Դ��Ҫ��
    emReturnValue_Invalid//������Ч,���ᱻ����
};
typedef struct tagResponse           //Request��Ϣ�Ļ�Ӧ��Ϣ(response��Ϣ)
{                           
    s32    m_nReqID;//��ˮ��/ϵ�к�,��ƥ��request�е���ˮ��/ϵ�к�
    emReturnValue m_emReturnVal;//request������ָʾ��
    tagResponse()
    {
        m_emReturnVal = emReturnValue_Ok;
        m_nReqID =((s32)time(NULL))%((s32)0x7fffffff);
    }
}TRsp;

//�Ǳ�(�Զ���)response��Ϣ
typedef struct tagNonStandardRsp: public TRsp, public TNonStandardMsg{}TNonStandardRsp;


//֪ͨ������Ϣ(notification)�Ļ���
typedef struct tagNotification
{
    s32    m_nCookie;//cookieֵ
}TNtf;

//��ȡMCU�ϵķ����б��������Ϣ,����Զ�mcu�����mcu�������Ѿ�����ķ���ģ�����Ϣ
#define TMCUServiceListReq TReq

//��ȡMCU�ϵ�ǰ�ٿ������л��������Ϣ���б�
typedef struct tagMCUConfListReq: public TReq
{
	s32 m_nSnapShot;//MCU����ֵ
}TMCUConfListReq;

//ͨ���������ֻ�û���ID��������Ϣ
typedef struct tagGetConfIDByNameReq:public TReq
{
	s8 m_aszConfName[STR_LEN];//��������
	s8 m_aszConfPass[STR_LEN];//��������,mcu�����ߵ�����Ҳͬ����Ч
}TGetConfIDByNameReq;

//������л��鼶����ע��ע������
typedef struct tagRegUnReg: public TReq     //��Զ�mcuע��ע����������Ϣ
{
    BOOL32 m_bReg;               //true:ע��;false ע��
}TRegUnRegReq;

//������л��鼶����ע��/ע���Ļ�Ӧ��Ϣ(�ɹ� m_emReturnValΪtrue������)
typedef struct tagRegUnRegRsp :public TRsp 
{
	BOOL32 m_bReg;  //true:ע��;false ע��            
}TRegUnRegRsp;

//
typedef struct tagPartID           //����μ��ߵ�ID,Ψһ�ı�ʾ����MCU������һ��������
                                  //����m_dwPID��0xffffffff��ʾ�����ӻ���;
{
    u32         m_dwPID;          // part id
    BOOL32      m_bLocal;         // true:����μ���ֱ���뱾��MCU���� 
                                 // false:����μ���ֱ����Զ�MCU����
    tagPartID ()
    {
        m_dwPID = 0;
        m_bLocal =FALSE;
    }
    inline BOOL32 IsSamePart(tagPartID tPeerPart)
    {
        if(m_dwPID == tPeerPart.m_dwPID && m_bLocal == tPeerPart.m_bLocal)
        {
            return TRUE;
        }
        return FALSE;
    }
    inline BOOL32 IsSamePart(u32 dwPID, BOOL32 bLocal)
    {
        if(m_dwPID == dwPID && m_bLocal == bLocal)
        {
            return TRUE;
        }
        return FALSE;
    }
    inline u32    GetPid() { return m_dwPID ;}
    inline void   SetPid(u32 dwPID) { m_dwPID = dwPID;}
    inline BOOL32 IsLocalPart(){ return m_bLocal;}
    inline BOOL32 IsRemotePart(){ return !m_bLocal;}
    inline BOOL32 IsEmptyPart(){ return m_dwPID == EMPTY_MT_PID;}
    inline void   SetEmpty(){ m_dwPID = EMPTY_MT_PID; m_bLocal = FALSE; }
    inline void   SetIsLocalPart(BOOL32 bLocal = TRUE) { m_bLocal = bLocal; }
    //
    inline BOOL32 IsLocalKdvMCU(){  return (m_dwPID  == CACSCONF_ID && m_bLocal);}
    inline BOOL32 IsRemoteRadMcu(){ return (m_dwPID == CACSCONF_ID && !m_bLocal);}

    inline void SetPartGid(u32 dwPid, BOOL32 bLocal)
    {
        m_dwPID  = dwPid;
        m_bLocal = bLocal;
    }
    
    inline void GetPartGid(u32 *pdwPid, BOOL32 *pbLocal)
    {
        if(pdwPid)
        {
            *pdwPid = m_dwPID;
        }
        if(pbLocal)
        {
            *pbLocal = m_bLocal;
        }
        return;
    }
}TPartID;

//��ȡMCU�ϵ�ǰ�ٿ������л����profile
//������ʱδ����������Ӧ��Ϣ�Ľṹ
typedef struct tagConfProfileReq:public TReq
{
    s32 m_nSnapShot;//
}TConfProfileReq;

//
typedef struct tagPartReq: public TPartID, public TReq{}TPartReq;

//�·�����(Floor)֪ͨ
typedef struct tagNewSpeakerNtf:public TPartID,public TNtf
{
    s32 m_nMixerID;  //Mixer ID
    tagNewSpeakerNtf(){memset(this, 0, sizeof(*this)); }
}TNewSpeakerNtf,*PTNewSpeakerNtf;

//
typedef enum 
{
        emMediaTypeNone,    //unknown,invalid
        emMediaTypeVideo,   //video
        emMediaTypeAudio,   //audio
        emMediaTypeData     //data
}emMediaType;               //ý������

typedef enum 
{
    emDirectionNone,       //unknown,invalid
    emDirectionIn,        //���ն˵�MCU
    emDirectionOut       //��MCU���ն�
}emMuteDirection;          //ĳһ��ý����������

typedef struct tagPartMediaChan:public TPartID
{
    emMediaType      m_emMediaType;        //ý������
    emMuteDirection  m_emMuteDirection;    //ý������������
    BOOL32           m_bMute;              //true:�жϸ÷����������false:�򿪸÷����ý������
    tagPartMediaChan(){memset(this, 0, sizeof(*this)); }
}TPartMediaChan; 

//�����Ա��/��/����ͨ����/�ر�֪ͨ
typedef struct tagPartMediaChanNtf:public TPartMediaChan,public TNtf{}TPartMediaChanNtf;

//�����Ա��/��/����ͨ����/�ر�����
typedef struct tagPartMediaChanReq:public TPartMediaChan,public TReq{}TPartMediaChanReq;

// һ����MCU���ն˵���Ƶ����淶�Ķ���
typedef struct tagViewOutInfo:public TPartID 
{    
    s32 m_nOutViewID;         //LayoutID,����Ļ�����ͼID
    s32 m_nOutVideoSchemeID;  //VideoSchemeID,��Ƶ�������ID
}TViewOutInfo,*PTViewOutInfo;

//����MCU�����Ƶ���������Ա
typedef struct tagSetOutReq :public TReq
{
    s32              m_dwPartCount;           //����MCU�����Ƶ���Լ����ն���Ŀ
    TViewOutInfo     m_tPartOutInfo[PART_NUM];//��Ƶ����淶���б�ÿһ���б�Ԫ�ض�����һ���ն˵���Ƶ�������

private:
    
     BOOL32 FindPartViewOutItem(u32 dwPartId, BOOL32 bLocal, s32 &nPartIndex)
     {
         for(nPartIndex =0; nPartIndex < m_dwPartCount; nPartIndex++)
         {
             if(m_tPartOutInfo[nPartIndex].IsEmptyPart())
             {
                 return FALSE;
             }
             if(m_tPartOutInfo[nPartIndex].IsSamePart(dwPartId, bLocal))
             {
                 return TRUE;
             }
         }
         return FALSE;
     }

public: 
    tagSetOutReq(){memset(this, 0, sizeof(*this)); }

    inline s32 GetPartCount(){ return m_dwPartCount;}

    s32 AddNewPartViewOutItem(u32 dwPartId, BOOL32 bLocal, s32 nOutViewID, s32 m_nOutVideoSchemeID)
    {
             s32 nPartIndex = 0;
             if( FindPartViewOutItem(dwPartId, bLocal, nPartIndex))
             {
                 return E_ALREADY_EXISTED;
             }
             if(nPartIndex >= PART_NUM)
             {
                 return E_TOO_MANY_ITEMS;
             }
             m_tPartOutInfo[nPartIndex].m_nOutViewID = nOutViewID;
             m_tPartOutInfo[nPartIndex].m_nOutVideoSchemeID = m_nOutVideoSchemeID;
             m_tPartOutInfo[nPartIndex].SetPartGid(dwPartId, bLocal);
             m_dwPartCount++;
             return S_RIGHT;
    }
    ////////////////
    s32 DelPartViewOutItem(u32 dwPartId, BOOL32 bLocal)
    {
        s32 nPartIndex = 0;
        if(! FindPartViewOutItem(dwPartId, bLocal, nPartIndex))
        {
            return E_NOT_EXISTED;
        }
        for(; nPartIndex < m_dwPartCount-1; nPartIndex++)
        {
            memcpy(&(m_tPartOutInfo[nPartIndex]), 
                   &(m_tPartOutInfo[nPartIndex + 1]), sizeof(TViewOutInfo));
        }
        m_dwPartCount--;
        return S_RIGHT;
    }
    
    s32 GetPartViewOutItem(u32 dwPartId, BOOL32 bLocal,s32 &nViewId, s32 &nVideoSchemeId)
    {
        s32 nPartIndex = 0;
        if(! FindPartViewOutItem(dwPartId, bLocal, nPartIndex))
        {
            return E_NOT_EXISTED;
        }
        nViewId        = m_tPartOutInfo[nPartIndex].m_nOutViewID;
        nVideoSchemeId = m_tPartOutInfo[nPartIndex].m_nOutVideoSchemeID;
        return S_RIGHT;
    }

    s32 GetPartViewOutItem(u32 dwPartId, BOOL32 bLocal,TViewOutInfo &tPartViewOut)
    {
        s32 nPartIndex = 0;
        if(! FindPartViewOutItem(dwPartId, bLocal, nPartIndex))
        {
            return E_NOT_EXISTED;
        }
        tPartViewOut.m_nOutViewID        = m_tPartOutInfo[nPartIndex].m_nOutViewID;
        tPartViewOut.m_nOutVideoSchemeID = m_tPartOutInfo[nPartIndex].m_nOutVideoSchemeID;
        tPartViewOut.m_dwPID             = m_tPartOutInfo[nPartIndex].m_dwPID;
        tPartViewOut.m_bLocal            = m_tPartOutInfo[nPartIndex].m_bLocal;
        return S_RIGHT;
    }

    s32 SetPartViewOutItem(u32 dwPartId, BOOL32 bLocal,s32 nViewId, s32 nVideoSchemeId)
    {
        s32 nPartIndex = 0;
        if(! FindPartViewOutItem(dwPartId, bLocal, nPartIndex))
        {
            return E_NOT_EXISTED;
        }
        m_tPartOutInfo[nPartIndex].m_nOutViewID        = nViewId;
        m_tPartOutInfo[nPartIndex].m_nOutVideoSchemeID = nVideoSchemeId;
        return S_RIGHT;
    }

    s32 SetPartViewOutItem(u32 dwPartId, BOOL32 bLocal,TViewOutInfo &tPartViewOut)
    {
        s32 nPartIndex = 0;
        if(! FindPartViewOutItem(dwPartId, bLocal, nPartIndex))
        {
            return E_NOT_EXISTED;
        }
        m_tPartOutInfo[nPartIndex].m_nOutViewID        = tPartViewOut.m_nOutViewID;
        m_tPartOutInfo[nPartIndex].m_nOutVideoSchemeID = tPartViewOut.m_nOutVideoSchemeID;
    }

    inline TViewOutInfo * GetItemByIndex(s32 nIndex)
    { return (nIndex >= 0 && nIndex < m_dwPartCount) ? &(m_tPartOutInfo[nIndex]) : NULL; }

}TSetOutReq,*PTSetOutReq;

//MCU�����Ƶ���������Ա��֪ͨ
typedef struct tagPartOutputNtf:public TPartID,public TNtf
{
    s32 m_nViewID; //�ն�������Ļ�����ͼID
    inline tagPartOutputNtf()
    {
        m_nViewID = m_dwPID = 0;
        m_bLocal = FALSE;
    }
}TPartOutputNtf, *PTPartOutPutNtf;


//���黨�����һ��,��ʾһ������Ա�Ļ�����Ϣ
typedef struct tagTRosterItem:public TPartID
{
    emConnState  m_emConnState;    //����״̬
}TRosterItem, *PTRosterItem;

//���黨����֪ͨ
typedef struct tagRosterList:public TNtf
{
    s32          m_nCount;               //�������¼����Ŀ
    TRosterItem  m_atRoster[PART_NUM];   //��¼���б�
private: 
    BOOL32 FindRosterItem(u32 dwPartId, BOOL32 bLocal, s32 &nIndex)
    {
        for(nIndex =0; nIndex < m_nCount; nIndex++)
        {
            if(m_atRoster[nIndex].IsEmptyPart())
            {
                return FALSE;
            }
            if(m_atRoster[nIndex].IsSamePart(dwPartId, bLocal))
            {
                return TRUE;
            }
        }
        return FALSE;
    }

public:

    inline tagRosterList(){ memset(this, 0, sizeof(*this));}

    BOOL32 AddRosterItem(u32 dwPartId, BOOL32 bLocal, emConnState emState)
    {
        s32  nRosterIndex = 0;
        if( FindRosterItem(dwPartId, bLocal, nRosterIndex))
        {
            return E_ALREADY_EXISTED;
        }

        if( nRosterIndex >= PART_NUM)
        {
            return E_TOO_MANY_ITEMS;
        }
        m_atRoster[nRosterIndex].m_dwPID = dwPartId;
        m_atRoster[nRosterIndex].m_bLocal = bLocal;
        m_atRoster[nRosterIndex].m_emConnState = emState;
        m_nCount ++;
        return S_RIGHT;
    }
    
    BOOL32 DelRosterItem(u32 dwPartId, BOOL32 bLocal, emConnState emState)
    {
        s32  nRosterIndex = 0;
        if(! FindRosterItem(dwPartId, bLocal, nRosterIndex))
        {
            return E_NOT_EXISTED;
        }
        for(; nRosterIndex < m_nCount-1; nRosterIndex++)
        {
            memcpy(&(m_atRoster[nRosterIndex]), 
                &(m_atRoster[nRosterIndex + 1]), sizeof(TRosterItem));
        }
        m_nCount--;
        return S_RIGHT;
    } 
    
    inline TRosterItem * GetItemByIndex(s32 nIndex)
    { return (nIndex >= 0 && nIndex < m_nCount) ? &(m_atRoster[nIndex]) : NULL; }

}TRosterList, *PTRosterList;

//������ͼ�Ӵ��ڵ�λ�ñ�־
typedef struct 
{
    s32  m_nViewID;//������ͼID
    u8   m_bySubframeIndex;//�Ӵ����ڻ�����ͼ��λ��(���մ����Ҵ��ϵ��µ�˳���0��ʼ����)
}TViewPos;

//(voice activate)������������,�ѵ�ǰ˵����/�����������Ļ����Ա����Ƶ��������ͼ���Ǹ��Ӵ�����
typedef struct tagVAReq:public TReq, public TViewPos{}TVAReq;

//�����Ա����Ƶ���������Ϣ
typedef struct tagPartVideoInfo
{
    s32       m_nViewCount;                    //�ն�(�����Ա)����Ƶ�ܹ����������ͼ��Ŀ
    TViewPos  m_anViewPos[MAX_VIEWS_PER_CONF]; //�ն�����Щ��ͼ��
    s32       m_nOutputViewID;                 //�ն˽����ĸ���ͼ
    s32       m_nOutVideoSchemeID;             //���뵽�ն˵���Ƶ����ID(��һ������֧�����ֻ����ʽ)                        
    
private:
    BOOL32 FindViewPos(s32 nViewID, u8 bySubframeIndex, s32 &nIndex)
    {
        for(nIndex =0; nIndex < m_nViewCount; nIndex++)
        {
            if(m_anViewPos[nIndex].m_nViewID == 0)
            {
                return FALSE;
            }
            if(m_anViewPos[nIndex].m_nViewID == nViewID && m_anViewPos[nIndex].m_bySubframeIndex ==bySubframeIndex)
            {
                return TRUE;
            }
        }
        return FALSE;
    }

public:
    tagPartVideoInfo()
    {
        memset(this,0,sizeof(*this));
    }
    BOOL32 AddViewPos(s32 nViewID,u8 bySubframeIndex)
    {
        s32  nVPosIndex = 0;
        if(nViewID == 0)
        {
            return S_RIGHT;
        }
        if(FindViewPos(nViewID, bySubframeIndex, nVPosIndex))
        {
            return E_ALREADY_EXISTED;
        }
        
        if( nVPosIndex >= MAX_VIEWS_PER_CONF)
        {
            return E_TOO_MANY_ITEMS;
        }
        
        m_anViewPos[nVPosIndex].m_nViewID         = nViewID;
        m_anViewPos[nVPosIndex].m_bySubframeIndex = bySubframeIndex;

        m_nViewCount ++;
        return S_RIGHT;
    }
   
    BOOL32 DelViewPos(s32 nViewID,u8 bySubframeIndex)
    {
        s32  nVPosIndex = 0;
        if(! FindViewPos(nViewID, bySubframeIndex, nVPosIndex))
        {
            return E_NOT_EXISTED;
        }
        for(; nVPosIndex < m_nViewCount-1; nVPosIndex++)
        {
            memcpy(&(m_anViewPos[nVPosIndex]), 
                &(m_anViewPos[nVPosIndex + 1]), sizeof(TViewPos));
        }
        m_nViewCount--;
        return S_RIGHT;
    }

    BOOL32 IsViewPosExist(s32 nViewID, u8 bySubframeIndex)
    {
        s32  nVPosIndex = 0;
        if(! FindViewPos(nViewID, bySubframeIndex, nVPosIndex))
        {
            return FALSE;
        }
        else
        {
            return TRUE;
        }
    }

    inline void SetVideoSpec(s32 nNewLID, s32 nNewSchemeID, s32 *nOldLID = NULL, s32 *nOldSchemeID = NULL)
    {
        if(nOldLID)
        {
            *nOldLID = m_nOutputViewID;
        }
        if(nOldSchemeID)
        {
            *nOldSchemeID = m_nOutVideoSchemeID;
        }
        m_nOutputViewID        = nNewLID;
        m_nOutVideoSchemeID = nNewSchemeID;
        return;
    }

    inline void GetVideoSpec(s32 *pnLID, s32 *pnSchemeID)
    {
        if(pnLID)
        {
            *pnLID = m_nOutputViewID;
        }
        if(pnSchemeID)
        {
            *pnSchemeID = m_nOutVideoSchemeID;
        }
    }

}TPartVideoInfo,*PTPartVideoInfo;


/*
 *����ߵ���Ƶ����Ƶ���������ͳ����Ϣ����������������/���ܵİ���Ŀ���������Ŀ��
 ����(jitter)�����,Ŀǰû�о��嶨��
*/
typedef struct tagPartAVStatis
{
  u32 m_dwTotalInBandWidth;
  u32 m_dwTotalOutBandWidth;
  u32 m_dwUnused_AudioIn;
  u32 m_dwUnused_AudioOut;
  u32 m_dwUnused_VideoIn;
  u32 m_dwUnused_VideoOut;
  // Currently We Define the bandwith with fixed value
  // because we did not decide to get extra info about part
  // Once we change to get the extra info, we should rewrite this code here.
  tagPartAVStatis()
  {
      m_dwTotalInBandWidth = 437720;
      m_dwTotalOutBandWidth = 437720; 
      m_dwUnused_AudioIn  = 0;
      m_dwUnused_AudioOut = 0;
      m_dwUnused_VideoIn  = 0;
      m_dwUnused_VideoOut = 0;
      
  }
}TPartAVStatis;


/*
 *����ߵ���Ϣ
*/
typedef struct tagPart:public TPartID
{
    s8			m_aszPartName[STR_LEN];     //part name
    s8			m_aszDialStr[STR_LEN];      //dial string
    u32			m_dwIP;            //part ip
    emEPType	m_emEPType;        //part type
    s8          m_aszEPDesc[STR_LEN];       //part des(product id)
    PayloadType m_emVideoIn;       //video in format (H263��G711.....None)
    PayloadType m_emVideoOut;      //.....
    PayloadType m_emVideo2In;      //.....
    PayloadType m_emVideo2Out;     //..... 
    PayloadType m_emAudioIn;       //.....
    PayloadType m_emAudioOut;      //..... 
    BOOL32      m_bDataMeeting;    //data meeting  
    BOOL32      m_bVideoMuteIn;    //whether or not video in mute(no camera)
    BOOL32      m_bVideoMuteOut;   //....(no dispaly)
    BOOL32      m_bAudioMuteIn;    //....(no mic)
	BOOL32      m_bAudioMuteOut;   //....(no audio player)
    BOOL32      m_bInvited;        //whether or not is Invited
    BOOL32      m_bMaster;         //whether or not Master ternial
    TTimeSpec   m_tStartTime;      //call start time
    emConnState m_emConnState;     //connect state
    BOOL32      m_bFECCEnable;     //whether or not enable FECC
    TPartVideoInfo m_tPartVideoInfo;   //��Ƶ���������Ϣ
    TPartAVStatis  m_tAVStatis;    //��Ƶ��Ƶ�������ͳ����Ϣ

    tagPart()
    {
        memset(this, 0, sizeof(*this));
    }
    inline void SetVideoAttr(PayloadType emVideoIn, PayloadType emVideoOut, 
                                PayloadType emVideo2In, PayloadType emVideo2Out, 
                                BOOL32 bVideoMuteIn, BOOL32 bVideoMuteOut)
    {
         m_emVideoIn      = emVideoIn;      
         m_emVideoOut     = emVideoOut; 
         m_emVideo2In      = emVideo2In;      
         m_emVideo2Out     = emVideo2Out; 
         m_bVideoMuteIn   = bVideoMuteIn;    
         m_bVideoMuteOut  = bVideoMuteOut;   
    }

    inline void GetVideoAttr(PayloadType *pemVideoIn, PayloadType *pemVideoOut, 
                                PayloadType *pemVideo2In, PayloadType *pemVideo2Out,
                                BOOL32 *pbVideoMuteIn, BOOL32 *pbVideoMuteOut)
    {
        if(pemVideoIn)
        { 
            *pemVideoIn = m_emVideoIn;
        }
        if(pemVideoOut)
        { 
            *pemVideoOut = m_emVideoOut; 
        }
        if(pemVideo2In)
        { 
            *pemVideo2In = m_emVideo2In;
        }
        if(pemVideo2Out)
        { 
            *pemVideo2Out = m_emVideo2Out; 
        }
        if(pbVideoMuteIn)
        { 
            *pbVideoMuteIn = m_bVideoMuteIn;
        }
        if(pbVideoMuteOut)
        { 
            *pbVideoMuteOut = m_bVideoMuteOut;
        }
        return;
    }
    
    inline void SetViewInAndOutAttr(TPartVideoInfo &tPartVideoInfo)
    {
        memcpy(&m_tPartVideoInfo, &tPartVideoInfo,sizeof(TPartVideoInfo));
    }

    inline TPartVideoInfo* GetViewInAndOutAttr()
    {
        return &m_tPartVideoInfo;
    }
    
    inline void SetAudioAttr(PayloadType emAudioIn, PayloadType emAudioOut, BOOL32 bAudioMuteIn, BOOL32 bAudioMuteOut)
    {
        m_emAudioIn      = emAudioIn;      
        m_emAudioOut     = emAudioOut;     
        m_bAudioMuteIn   = bAudioMuteIn;    
        m_bAudioMuteOut  = bAudioMuteOut;   
    }

    inline void GetAudioAttr(PayloadType *pemAudioIn, PayloadType *pemAudioOut, BOOL32 *pbAudioMuteIn, BOOL32 *pbAudioMuteOut)
    {
        if(pemAudioIn)
        { 
            *pemAudioIn = m_emAudioIn;
        }
        if(pemAudioOut)
        { 
            *pemAudioOut = m_emAudioOut; 
        }
        if(pbAudioMuteIn)
        { 
            *pbAudioMuteIn = m_bAudioMuteIn;
        }
        if(pbAudioMuteOut)
        { 
            *pbAudioMuteOut = m_bAudioMuteOut;
        }
        return;
    }

    inline void SetNameAttr(const s8 *pszName, s32 nNameLen, const s8 *pszDescr, s32 nDescrLen)
    {
        // assert(pszName != NULL);
        s32 nStrLen = (nNameLen >= STR_LEN ? STR_LEN -1 : nNameLen );
        strncpy(m_aszPartName, pszName, nStrLen);
        m_aszPartName[nStrLen] = '\0';

        if(pszDescr != NULL && nDescrLen > 0)
        {
            nStrLen = (nDescrLen >= STR_LEN ? STR_LEN -1 : nDescrLen );
            strncpy(m_aszDialStr, pszDescr, nStrLen);
            m_aszDialStr[nStrLen] = '\0';
        }
        else
        {
            m_aszDialStr[0] = '\0';
        }
    }

    inline void GetNameAttr(s8 *pszName, s32 nNameLen, s8 *pszDescr, s32 nDescrLen)
    {
        if(pszName != NULL && nNameLen > 0)
        {
            s32 nStrLen = (nNameLen >= STR_LEN ? STR_LEN -1 : nNameLen );
            strncpy(pszName, m_aszPartName, nStrLen);
            pszName[nStrLen] = '\0';  
        }

        if(pszDescr != NULL && nDescrLen > 0)
        {
            s32 nStrLen = (nDescrLen >= STR_LEN ? STR_LEN -1 : nDescrLen);
            strncpy(pszDescr, m_aszDialStr, nStrLen);     
            pszDescr[nStrLen] = '\0';
        }
    }

    inline void SetDialStr(const s8 *pszDialStr, s32 nLen)
    {
       if(pszDialStr !=NULL && nLen >0)
       {
           s32 nStrLen = (nLen >= STR_LEN ? STR_LEN -1 : nLen);
           strncpy(m_aszDialStr, pszDialStr, nStrLen);
           m_aszDialStr[nStrLen] = '\0';
       }
    }

    inline s8 * GetDialStr() { return this->m_aszDialStr; }

    inline void SetEntityAttr(emConnState emState, emEPType emEntityType, BOOL32 bFECCEnable, BOOL32 bMaster, BOOL32 bInvited)
    {
        m_emConnState    = emState;  
        m_emEPType       = emEntityType;
        m_bFECCEnable    = bFECCEnable;     
        m_bMaster        = bMaster;       
        m_bInvited       = bInvited;       
    }
    inline BOOL32 IsFECCEnable(){ return m_bFECCEnable;}
    inline BOOL32 IsMaster() { return m_bMaster;}
    inline BOOL32 IsInvited() { return m_bInvited;}
    inline emConnState GetConnState() { return m_emConnState;}
    inline void   SetConnState(emConnState emState) { m_emConnState = emState;}
    inline void   StopAsVideoSrc() { m_tPartVideoInfo.m_nViewCount = 0;}
    inline BOOL32 IsVideoSrc() { return (m_tPartVideoInfo.m_nViewCount > 0);}
    inline u32    GetTotalBandWith() { return m_tAVStatis.m_dwTotalInBandWidth + m_tAVStatis.m_dwTotalOutBandWidth;}

    inline void GetEntityAttr(emConnState *pemState, BOOL32 *pbFECCEnable, BOOL32 *pbMaster, BOOL32 *pbInvited)
    {
        if(pemState)
        { 
            *pemState = m_emConnState;
        }
        if(pbFECCEnable)
        { 
            *pbFECCEnable = m_bFECCEnable; 
        }
        if(pbMaster)
        { 
            *pbMaster = m_bMaster;
        }
        if(pbInvited)
        { 
            *pbInvited = m_bInvited;
        }
        return;
    }
    inline void GetVideoScheme(s32 *pnViewId, s32 *pnVideoSchemeId)
    {
        m_tPartVideoInfo.GetVideoSpec(pnViewId,pnVideoSchemeId);
    }
    inline void SetVideoScheme(s32 nViewId, s32 nVideoSchemeId)
    {
        m_tPartVideoInfo.SetVideoSpec(nViewId, nVideoSchemeId, NULL, NULL);
    }
}TPart,*PTPart;

//������������ߵ���Ϣ
typedef struct tagConfPartInfo
{
    s32    m_dwPartCount;       //fact part count
    s32    m_nSnapShot;         //����Ŀ���ֵ
        //The first Element Denotes MCU, The Record series from second Denote Terminals 
    TPart  m_atParts[PART_NUM]; // part list 
 private:
     BOOL32 FindPart(u32 dwPartId, BOOL32 bLocal, s32 &nIndex)
     {
         for(nIndex =0; nIndex < m_dwPartCount; nIndex++)
         {
             if(m_atParts[nIndex].IsEmptyPart())
             {
                 return FALSE;
             }
             if(m_atParts[nIndex].IsSamePart(dwPartId, bLocal))
             {
                 return TRUE;
             }
         }
         return FALSE;
     }
     
 public:
     void Clear()
     {
         memset(this, 0, sizeof(*this));
     }
     tagConfPartInfo()
     {
         memset(this, 0, sizeof(*this));
     }
     s32 AddPart(TPart &tPart, BOOL32 bReplace = TRUE)
     {
         s32  nPartIndex = 0;
         if(FindPart(tPart.m_dwPID, tPart.m_bLocal, nPartIndex))
         {
             if(bReplace)
             {
                 memcpy(&m_atParts[nPartIndex], &tPart, sizeof(TPart));
                 return S_RIGHT;
             }
             else
             {
                 return E_ALREADY_EXISTED;
             }
         }
         if( nPartIndex >= PART_NUM)
         {
             return E_TOO_MANY_ITEMS;
         }
         
         memcpy(&m_atParts[nPartIndex], &tPart, sizeof(TPart));
         m_dwPartCount ++;
         return S_RIGHT;
     }

    s32 DelPart(u32 dwPartId, BOOL32 bLocal)
     {
         s32 nPartIndex = 0;
         if(! FindPart(dwPartId, bLocal, nPartIndex))
         {
             return E_NOT_EXISTED;
         }
         for(; nPartIndex < m_dwPartCount-1; nPartIndex++)
         {
             memcpy(&(m_atParts[nPartIndex]), 
                 &(m_atParts[nPartIndex + 1]), sizeof(TPart));
         }
         m_dwPartCount--;
         return S_RIGHT;
     }
    
     s32 Disconnect(u32 dwPartId, BOOL32 bLocal, u32 dwNewPartId)
     {
         s32 nPartIndex = 0;
         if(! FindPart(dwPartId, bLocal, nPartIndex))
         {
             return E_NOT_EXISTED;
         }
         if(m_atParts[nPartIndex].GetConnState() == emConnStateDisconnected)
         {
             return E_ALREADY_EXISTED;
         }
         m_atParts[nPartIndex].m_dwPID = dwNewPartId;
         m_atParts[nPartIndex].SetConnState(emConnStateDisconnected);
         memset(&(m_atParts[nPartIndex].m_tPartVideoInfo), 0, sizeof(TPartVideoInfo));
         
         return S_RIGHT;
     }
    
     TPart *GetPart(u32 dwPartId, BOOL32 bLocal)
     {
         s32 nPartIndex = 0;
         if(! FindPart(dwPartId, bLocal, nPartIndex))
         {
             return NULL;
         }
         return &(m_atParts[nPartIndex]);
     }

     inline TPart *GetLocalMCU()
     {
         return GetPart(CACSCONF_ID, TRUE);
     }

     inline TPart *GetPeerMCU()
     {
         return GetPart(CACSCONF_ID, FALSE);
     }

     BOOL32 IsPartExist(u32 dwPartId, BOOL32 bLocal)
     {
         s32 nPartIndex = 0;
         if(! FindPart(dwPartId, bLocal, nPartIndex))
         {
             return FALSE;
         }
         return TRUE;
     }
     
     inline TPart *GetItemByIndex(s32 nPosFrom)
     {
         return (nPosFrom >= 0 && m_dwPartCount > nPosFrom ? &m_atParts[nPosFrom] : NULL);
     }
     
}TConfPartInfo;

//�Է�MCU�����ӻ���Ļ�Ӧ�б�
typedef struct tagPartListRsp :public TConfPartInfo,public TRsp
{
   BOOL32 m_bLastPack;			//whether or not last pack��used only while receiving
   public:
    tagPartListRsp() { m_emReturnVal = emReturnValue_Ok; m_bLastPack = TRUE;}
    void Clear()
    { 
        memset(this, 0, sizeof(*this));
        m_emReturnVal = emReturnValue_Ok; 
        m_bLastPack = TRUE;
    }
    void BuildToPartListRsp(TConfPartInfo &tConfPart)
    {
        s32 nMemSize = 0;
        nMemSize = tConfPart.m_dwPartCount * sizeof(TPart);
        memcpy(&m_atParts[0], &tConfPart.m_atParts[0], nMemSize);
        m_nSnapShot = tConfPart.m_nSnapShot;
        m_dwPartCount = tConfPart.m_dwPartCount ;
        m_bLastPack = TRUE;
        m_emReturnVal = emReturnValue_Ok;
    }
    
    BOOL32 ExtractConfPartList(TConfPartInfo &tConfPart)
    {
        s32 nIndex      = 0;
        while( nIndex < m_dwPartCount)
        {
            tConfPart.AddPart(m_atParts[nIndex]);
            nIndex ++;
        }
        if(m_bLastPack)        
        {
            tConfPart.m_nSnapShot = m_nSnapShot;
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
}TPartListRsp,*PTPartListRsp;

//PartList��Ϣ�շ�ͷ�ṹ�������m_dwPartCount��TPart�ṹ
typedef struct tagPartListMsg: public TRsp
{
    s32    m_dwPartCount;       //fact part count
    s32    m_nSnapShot;         //����Ŀ���ֵ
    BOOL32 m_bLastPack;         //whether or not last pack��used only while receiving
} TPartListMsg,*PTPartListMsg;


//�����ն˼������Ĳ���
typedef struct tagInvitePart
{
    s8   m_aszDialStr[STR_LEN];   //dial string ("123"��"100.1.1.1"��"h323id")
    u32  m_dwCallRate;                //call rate (kbps)
    
    //optional,advanced invitation parameter
    TPartVideoInfo m_tPartVideoInfo;
    
    tagInvitePart()
    {
        memset(this, 0, sizeof(*this));
    }
    
    void SetBasicInviteeParam(const s8 *pszDialStr, s32 nStrLen, u32 dwCallRate)
    {
        if(pszDialStr != NULL && nStrLen >0)
        {
            nStrLen = (nStrLen >= STR_LEN ? STR_LEN -1 : nStrLen );
            strncpy(m_aszDialStr, pszDialStr, nStrLen);
            m_aszDialStr[nStrLen] = '\0';           
        }
        m_dwCallRate = dwCallRate;
    }

    void GetBasicInviteeParam(s8 *pszDialStr, s32 nStrLen, u32 *pdwCallRate)
    {
        if(pszDialStr != NULL && nStrLen >0)
        {
            nStrLen = (nStrLen >= STR_LEN ? STR_LEN -1 : nStrLen );
            strncpy(pszDialStr, m_aszDialStr, nStrLen);
            pszDialStr[nStrLen] = '\0';
        }
        if(pdwCallRate)
        {
            *pdwCallRate = m_dwCallRate;
        }
        return;
    }

    inline void SetInviteeSetInAndOutAttr(TPartVideoInfo &tPartVideoInfo)
    {
        memcpy(&m_tPartVideoInfo, &tPartVideoInfo, sizeof(TPartVideoInfo));
    }

    inline TPartVideoInfo GetInviteeSetInAndOutAttr()
    {
       return m_tPartVideoInfo;
    }
  
}TInvitePart,*PTInvitePart;


/*
  ���������뼶���������Ϣ��  
*/
typedef struct tagInvitePartReq: public TReq
{
	s32          m_nCount;           //ͬʱ��Ҫ��Ķ������Ŀ
    TInvitePart  m_atPart[PART_NUM]; //�����������Ϣ
public:
     tagInvitePartReq()
     {
        memset(this, 0, sizeof(*this));
     }

     inline BOOL32 AddInvitee(TInvitePart &tInvitee)
     {
         if(m_nCount >= PART_NUM)
         {
             return FALSE;
         }
         memcpy(&m_atPart[m_nCount], &tInvitee,sizeof(TInvitePart));
         m_nCount++;
         return TRUE;
     }

     inline TInvitePart *GetItemByIndex(s32 nPos)
     { return (nPos >= 0 && nPos < m_nCount) ? &(m_atPart[nPos]) : NULL; }

}TInvitePartReq;

//����Ҫ���Ѿ��Ͽ����ն˼������
typedef struct tagReinvitePartReq: public TPartID, public TReq{}TReInvitePartReq;

//MCU_MCU_CALL_ALERTING_NTF ��Ϣ��
typedef struct tagCallNtf : public TPartID, public TNtf
{
	s8   m_aszDialStr[STR_LEN];   //dial string ("123"��"100.1.1.1"��"h323id")
   
    tagCallNtf()
    {
        memset(this, 0, sizeof(*this));
    }
    
    void inline GetPartCallingParam(s32 *pdwPartId, BOOL32 *pbLocal,s8 *pszDialStr, s32 nStrLen)
    {
        if(pdwPartId)
        {
            *pdwPartId = m_dwPID;
        }
        if(pbLocal)
        {
            *pbLocal = m_bLocal;
        }
        if(pszDialStr != NULL && nStrLen >0)
        {
            nStrLen = (nStrLen >= STR_LEN ? STR_LEN -1 : nStrLen );
            strncpy(pszDialStr, m_aszDialStr, nStrLen);
            pszDialStr[nStrLen] = '\0';
        }
    }

    void inline SetPartCallingParam(u32 dwPartId, BOOL32 bLocal,s8 *pszDialStr, s32 nStrLen)
    {
        m_dwPID  = dwPartId;
        m_bLocal = bLocal;
        if(pszDialStr != NULL && nStrLen >0)
        {
            nStrLen = (nStrLen >= STR_LEN ? STR_LEN -1 : nStrLen );
            strncpy(m_aszDialStr, pszDialStr, nStrLen);
            m_aszDialStr[nStrLen] = '\0';
        }
    }
}TCallNtf;

//�����ն����ͼ�񵽻����ĳ����ͼ
typedef struct tagSetInReq:public TPartID, public TReq
{
    s32 m_nViewID;          //ͼ���������Ļ�����ͼ
    u8  m_bySubFrameIndex;  //������ͼ�е���ͼ��(subframe)����
    tagSetInReq()
    {
        memset(this, 0, sizeof(*this));
    }
    
    void SetPartSetInParam(u32 dwPartId, BOOL32 bLocal, s32 nViewID, u8 bySubFrameIndex)
    {
        m_dwPID =  dwPartId;
        m_bLocal = bLocal;
        m_nViewID = nViewID;
        m_bySubFrameIndex = bySubFrameIndex;
    }

    void GetPartSetInParam(s32 *pdwPartId, BOOL32 *pbLocal, s32 *pnViewID, u8 *pbySubFrameIndex)
    {
        if(pdwPartId)
        {
            *pdwPartId = m_dwPID;
        }
        if(pbLocal)
        {
            *pbLocal = m_bLocal;
        }
        if(pnViewID)
        {
            *pnViewID = m_nViewID;
        }
        if(pbySubFrameIndex)
        {
            *pbySubFrameIndex = m_bySubFrameIndex;
        }
    }
    
}TSetInReq;

/*
 *����ߴӼ��������жϿ���ͨ�棬
*/
typedef struct tagDiscPartNF : public TPartID, public TNtf
{
    u32 m_dwNewPID;   //new part id
    tagDiscPartNF()
    {
        m_dwNewPID = 0;
    }
}TDiscPartNF,*PTDiscPartNF;

//��������Ϣ�����ܻ��ж��speaker������ֻ���ƶ�һ��
typedef struct tagAudioMixerInfo
{
    s32    m_nMixerID;             //mixer ID
    u32    m_dwSpeakerPID;         //speaker Pid
    BOOL32 m_bLocal;               //romote or local?
    tagAudioMixerInfo()
    {
        m_nMixerID = m_dwSpeakerPID = 0;
        m_bLocal = FALSE;
    }
    inline BOOL32 IsSpeakerExist(u32 dwPartId, BOOL32 bLocal)
    {
        return (m_dwSpeakerPID == dwPartId && m_bLocal == bLocal);
    }
}TAudioMixerInfo, *PTAudioMixerInfo;

//MCU�Ļ���������Ϣ
typedef struct tagConfAudioInfo:public TRsp
{
    u8 m_byMixerCount;                                 //��������Ŀ
    u8 m_byDefaultMixerIndex;                          //ȱʡ����������������ʾ,��Ҳ�ǵ�ǰ���ڲ����Ļ�����
    s32 m_nSnapShot;                                    //�������ֵ
    TAudioMixerInfo m_tMixerList[MAX_MIXERS_PER_CONF]; //�������б�

 private:
     BOOL32 FindSpeaker(u32 dwPartId, BOOL32 bLocal, s32 &nMixerIndex)
     {
         for(nMixerIndex =0; nMixerIndex < m_byMixerCount; nMixerIndex++)
         {
             if(m_tMixerList[nMixerIndex].m_nMixerID == 0 || m_tMixerList[nMixerIndex].m_dwSpeakerPID == 0)
             {
                 return FALSE;
             }
             if(m_tMixerList[nMixerIndex].IsSpeakerExist(dwPartId, bLocal))
             {
                 return TRUE;
             }
         }
         return FALSE;
     }
 public:
     tagConfAudioInfo()
     {
         memset(this, 0, sizeof(*this));
         m_emReturnVal = emReturnValue_Ok;
         m_nSnapShot = 0;
     }

     void Clear(void)
     {
         memset(this, 0, sizeof(*this));
         m_emReturnVal = emReturnValue_Ok;
         m_nSnapShot = 0;
     }
     
     BOOL32 AddNewSpeaker(u32 dwPartId, BOOL32 bLocal, s32 nMixerId)
     {
         s32 nMixerIndex = 0;
         if(FindSpeaker(dwPartId, bLocal, nMixerIndex))
         {
             m_tMixerList[nMixerIndex].m_nMixerID = nMixerId;
             return FALSE;
         }
         if(nMixerIndex >= MAX_MIXERS_PER_CONF)
         {
             return FALSE;
         }

         m_tMixerList[nMixerIndex].m_dwSpeakerPID = dwPartId;
         m_tMixerList[nMixerIndex].m_bLocal       = bLocal;
         m_tMixerList[nMixerIndex].m_nMixerID     = nMixerId;

         m_byMixerCount++;
         return TRUE;   
     }
     
     BOOL32 DelSpeaker(u32 dwPartId, BOOL32 bLocal)
     {
         s32 nMixerIndex = 0;
         if(! FindSpeaker(dwPartId, bLocal, nMixerIndex))
         {
             return E_NOT_EXISTED;
         }
         
         if(IsCurrentSpeaker(dwPartId, bLocal))
         {
             m_byDefaultMixerIndex = 0;
         }

         for(; nMixerIndex < m_byMixerCount-1; nMixerIndex++)
         {
             memcpy(&(m_tMixerList[nMixerIndex]), 
                 &(m_tMixerList[nMixerIndex + 1]), sizeof(TAudioMixerInfo));
         }

         m_byMixerCount--;
         return S_RIGHT;        
     }
     
     inline void GetCurrentSpeaker(u32 &dwPartId, BOOL32 &bLocal)
     {
         dwPartId = m_tMixerList[m_byDefaultMixerIndex].m_dwSpeakerPID;
         bLocal   = m_tMixerList[m_byDefaultMixerIndex].m_bLocal;
     }

     s32 SetCurrentSpeaker(u32 dwPartId, BOOL32 bLocal)
     {
         s32 nMixerIndex = 0;
         if(FindSpeaker(dwPartId, bLocal, nMixerIndex))
         {
             m_byDefaultMixerIndex = nMixerIndex;
             return S_RIGHT;
         }
         s32 nNewMixerId = (nMixerIndex + 1) * 10;
         AddNewSpeaker(dwPartId, bLocal, nNewMixerId);
         m_byDefaultMixerIndex = nMixerIndex;
         return nNewMixerId;
     }

     inline BOOL32 IsCurrentSpeaker(u32 dwPartId, BOOL32 bLocal)
     {
         return (m_tMixerList[m_byDefaultMixerIndex].m_dwSpeakerPID == dwPartId
                && m_tMixerList[m_byDefaultMixerIndex].m_bLocal == bLocal);
     }
}TConfAudioInfo;



//������ͼ���β��ֱ��֪ͨ
typedef struct tagConfViewChgNtf: public TNtf
{
    s32                   m_nViewID;                                 //�������β��ֱ仯�Ļ�����ͼID
    u8                    m_dwSubFrameCount;                           //�仯��ļ��β��ֻ��ֳɵ���ͼ����Ŀ(subframe)
}TConfViewChgNtf;

//MCU����Ƶ�������
typedef struct tagOutPutVideoSchemeInfo
{
    s32           m_nOutputVideoSchemeID;   //��Ƶ�������ID
    u32           m_dwMaxRate;              //max rate (kbps)
    u32           m_dwMinRate;              //min rate (kbps)
    BOOL32        m_bCanUpdateRate;         // whether or not enable update rate
    s32           m_nFrameRate;             // frame rate (30��25)
    PayloadType   m_emPayLoad;              // payload    (h261,h263,etc)
    tagOutPutVideoSchemeInfo()
    {
        memset(this, 0, sizeof(*this));
    }
}TOutPutVideoSchemeInfo,*PTOutPutVideoSchemeInfo;


//һ��������ͼ�Ķ��壬������һϵ�еļ��β��֣�һϵ�е���ͼ��ƵԴ(��pid����־)���б�
//�Լ���ѡ������û�����ͼ�ļ�����Ƶ�������(rad mcu ������ĸ�).
typedef struct tagViewInfo
{
    s32                m_nViewId;                                           //������ͼ ID
    emResolution       m_emRes;                                             //������ͼͼ��ķֱ���
    u8                 m_byCurrentGeometryIndex;                            //������ͼ��ǰ����ʹ��(���)�ļ��β���,���ڼ��β����б��е�����������
    u8                 m_byGeometryCount;                                   //���β��ֵ���Ŀ
    u8                 m_abyGeometryInfo[MAX_GEOMETRYS_PER_VIEW];            //���β����б�
    u8                 m_byContributePIDCount;                              //������ͼ����ƵԴ����Ŀ
    TPartID            m_atContributePIDs[MAX_SUBFRAMES_PER_GEOMETRY];         //��ƵԴ�б�
    u8                 m_byVideoSchemeCount;                                //��ѡ����Ƶ���������Ŀ
    TOutPutVideoSchemeInfo    m_atVideoSchemeList[MAX_VIDEOSCHEMES_PER_VIEW];     //��Ƶ��������б�
  
    //add 2007.04.28
    BOOL32             m_bAutoSwitchStatus;
    BOOL32             m_bDynamic;
    s32                m_nAutoSwitchTime;
    s32                m_nVideoRole;
    

    inline tagViewInfo()
    {
        memset(this, 0, sizeof(*this));
    }
    
    inline void SetViewResolution(emResolution emRes)
    {
        m_emRes = emRes;
    }
    
    inline emResolution GetViewResolution()
    {
        return m_emRes;
    }
    
    inline void GetCurrentContributerList(TPartID **pptContributerParts, s32 &nArrayLen, s32 *pnCurrentSubframes)
    {
        if(pptContributerParts)
        {
           *pptContributerParts = m_atContributePIDs;
            nArrayLen = m_byContributePIDCount;
        }
        if(pnCurrentSubframes)
        {
           *pnCurrentSubframes = m_abyGeometryInfo[m_byCurrentGeometryIndex];
        }
        return;
    }

    inline BOOL32 SetCurrentContributerList(TPartID *ptContributerParts, s32 nArrayLen)
    {
        if(ptContributerParts != NULL && nArrayLen > 0)
        {
            s32 nSubFrameCount = 0;
            nSubFrameCount =(nArrayLen <= MAX_SUBFRAMES_PER_GEOMETRY ?
                                     nArrayLen : MAX_SUBFRAMES_PER_GEOMETRY);
            s32 nIndex = 0;
            while(nIndex < MAX_SUBFRAMES_PER_GEOMETRY && m_abyGeometryInfo[nIndex] != 0 && m_abyGeometryInfo[nIndex] != nSubFrameCount)
            {
                nIndex ++;
            }
            if(nIndex >= MAX_SUBFRAMES_PER_GEOMETRY)
            {
                return FALSE;
            }
            if(m_abyGeometryInfo[nIndex] == 0)
            {
                m_byContributePIDCount ++;
                m_byGeometryCount ++;
                m_abyGeometryInfo[nIndex] = nSubFrameCount;  
            }
            m_byCurrentGeometryIndex = nIndex;
            memcpy(m_atContributePIDs, ptContributerParts, sizeof(TPartID)*nSubFrameCount);
        }
        else
        {
            m_byGeometryCount        = 1;
            m_abyGeometryInfo[0]     = 1;
            m_byCurrentGeometryIndex = 0;
            m_byContributePIDCount   = 0;
        }
        return TRUE;
    }

    inline void SetGeometryList(u8 *pbyGeometryList, s32 nItemCount, s32 nIndexCurrentGeometry = 0)
    {
        s32 nGeometryCount = 0;
        nGeometryCount = (nItemCount < MAX_GEOMETRYS_PER_VIEW ?
                         nItemCount : MAX_GEOMETRYS_PER_VIEW);
        memcpy(m_abyGeometryInfo, pbyGeometryList,nGeometryCount * sizeof(u8));
        m_byGeometryCount = nGeometryCount;
        m_byCurrentGeometryIndex = ((m_byGeometryCount -1 > nIndexCurrentGeometry) ?
                                    nIndexCurrentGeometry : m_byGeometryCount -1);
        return;
    }
    
    inline void GetGeometryList(u8 **ppbyGeometryList, s32 *pnItemCount, s32 *pnIndexCurrentGeometry = NULL)
    {
        if(ppbyGeometryList && pnItemCount) 
        {
            *ppbyGeometryList = m_abyGeometryInfo;
            *pnItemCount      = m_byGeometryCount;
        }
        if(pnIndexCurrentGeometry)
        {
            *pnIndexCurrentGeometry = m_byCurrentGeometryIndex;
        }
        return;
    }
    
    inline void SetVideoSchemeList(TOutPutVideoSchemeInfo *ptSchemeList, s32 nItemCount)
    {
        this->m_byVideoSchemeCount = nItemCount;
        memcpy(this->m_atVideoSchemeList, ptSchemeList, nItemCount * sizeof(TOutPutVideoSchemeInfo));
    }

    inline void GetVideoSchemeList(TOutPutVideoSchemeInfo **pptSchemeList, s32 &nItemCount)
    {
        *pptSchemeList = this->m_atVideoSchemeList;
        nItemCount = this->m_byVideoSchemeCount;
        return;
    }
    
    inline s32 GetViewId() { return m_nViewId;}
    inline void SetViewId(s32 nViewId) { m_nViewId = nViewId;}

}TView, *PTView;

//
typedef struct tagConfVideInfoReq: public TReq
{
    u8          m_bFullInfo;    //�Ƿ������ͼ��β�����ͼ
    tagConfVideInfoReq(){ m_bFullInfo = TRUE; }
}TConfVideInfoReq;
//���������ڵ���MCU�ϵ���Ƶ���������Ϣ
typedef struct tagConfVideoInfo:public TRsp
{
    u8          m_byConfViewCount;                              //������ͼ����Ŀ
    //Ĭ��ʹ�õĻ�����ͼ,������MCUֱ�����ն˻���MCU�����ӽ���ʱû��ָ��������ͼ��Ϣ��
    //��Ĭ�Ϲۿ��û�����ͼ
    u8          m_byDefaultViewIndex;                            //Ĭ�ϻ�����ͼ����
    u8          m_bFullInfo;                                     //�Ƿ��ͼ��β�����ͼ
    s32         m_nSnapShot;                                     //�������ֵ
    TView       m_atViewInfo[MAX_VIEWS_PER_CONF]; //������ͼ�б�
    
    private:
        BOOL32 FindView(s32 nViewId, s32 &nViewIndex)
        {
            for(nViewIndex =0; nViewIndex < m_byConfViewCount; nViewIndex++)
            {
                if(m_atViewInfo[nViewIndex].m_nViewId == 0)
                {
                    return FALSE;
                }
                if(m_atViewInfo[nViewIndex].m_nViewId == nViewId)
                {
                    return TRUE;
                }
            }
            return FALSE;
        }
        
    public:

        inline tagConfVideoInfo()
        {
            m_byConfViewCount = m_byDefaultViewIndex = 0;
            m_emReturnVal = emReturnValue_Ok;
            m_bFullInfo = TRUE;
        }
        inline void Clear(void)
        {
            memset(this, 0, sizeof(*this));
            m_byConfViewCount = m_byDefaultViewIndex = 0;
            m_emReturnVal = emReturnValue_Ok;
        }
        s32 AddView(TView &tView, BOOL32 bDefaultView = FALSE, BOOL32 bReplace = TRUE)
        {
            s32 nViewIndex = 0;
            if( FindView(tView.GetViewId(), nViewIndex))
            {
                if(bReplace)
                {
                    memcpy(&m_atViewInfo[nViewIndex], &tView, sizeof(TView));
                    if(bDefaultView)
                    {
                        m_byDefaultViewIndex = (u8)nViewIndex;
                    }
                    return S_REPLACED;
                }
                else
                {
                    if(bDefaultView)
                    {
                        m_byDefaultViewIndex = (u8)nViewIndex;
                    }
                    return E_ALREADY_EXISTED;
                }
            }

            if(nViewIndex >= MAX_VIEWS_PER_CONF)
            {
                return E_TOO_MANY_ITEMS;
            }

            memcpy(&m_atViewInfo[nViewIndex], &tView, sizeof(TView));
            if(bDefaultView)
            {
               m_byDefaultViewIndex = (u8)nViewIndex;
            }

            m_byConfViewCount++;
            return S_RIGHT;  
        }
        
        s32 DelView(s32 nViewId)
        {
            s32 nViewIndex = 0;
            if(! FindView(nViewId, nViewIndex))
            {
                return E_NOT_EXISTED;
            }
            if(nViewIndex == m_byDefaultViewIndex)
            {
                m_byDefaultViewIndex = 0;
            }
            memmove(&m_atViewInfo[nViewIndex], &m_atViewInfo[nViewIndex +1],
                   sizeof(TView) * (m_byConfViewCount - nViewIndex - 1));
            
            m_byConfViewCount--;
            return S_RIGHT;
        }
        
        s32 GetView(s32 nViewId, TView **pptView)
        {
            s32 nViewIndex = 0;
            if(! FindView(nViewId, nViewIndex))
            {
                *pptView = NULL;
                 return E_NOT_EXISTED;
            }
            if(pptView)
            {
                *pptView = &m_atViewInfo[nViewIndex];
                return nViewIndex;
            }
            return FALSE;
        }
        
        BOOL32 IsViewExist(s32 nViewId)
        {
            s32 nViewIndex = 0;
            if(! FindView(nViewId, nViewIndex))
            {
                return FALSE;
            }
            return TRUE;
        }
        inline TView* GetItemByIndex(s32 nIndex)
        {
           return nIndex >= 0 && nIndex < m_byConfViewCount ?
               &m_atViewInfo[nIndex] : NULL;
        }
        
        inline s32 GetDefaultViewId()
        { 
            return m_atViewInfo[m_byDefaultViewIndex].GetViewId();
        }

        void DelPartRelationship(s32 nPId, BOOL32 bLocal)
        {
            s32 nIndex            = 0;
            TView *ptView         = NULL;
            TPartID *ptPartId     = NULL;
            s32     nContributors = 0;
            while(ptView = GetItemByIndex(nIndex))
            {
                ptView->GetCurrentContributerList(&ptPartId, nContributors, NULL);
                while(nContributors-- > 0)
                {
                    if((ptPartId + nContributors)->IsSamePart(nPId, bLocal))
                    {
                        //will 
                        (ptPartId + nContributors)->SetEmpty();
                    }
                }           
                nIndex ++;
            }
        }
}TConfVideoInfo;


//add 2007.04.28
typedef struct tagAutoswitchReq: public TReq     //
{
  
    s32         m_nLid;
    s32         m_nAutoSwitchTime;
    s32         m_nAutoSwitchLevel;
    BOOL32      m_bAutoSwitchOn;

public: 
    tagAutoswitchReq()
    {
        Clear();
    }


    void Clear()
    {
        memset(this, 0, sizeof(tagAutoswitchReq));
    }
    
    void SetLid(s32 nLid)
    {
        m_nLid = nLid;
    }

    s32  GetLid()
    {
        return m_nLid;
    }

    void SetAutoSwitchTime(s32 nTime)
    {
        m_nAutoSwitchTime = nTime;
    }

    s32 GetAutoSwitchTime()
    {
        return m_nAutoSwitchTime;
    }

    void SetAutoSwitchLevel(s32 nLevel)
    {
        m_nAutoSwitchLevel = nLevel;
    }

    s32 GetAutoSwitchLevel()
    {
        return m_nAutoSwitchLevel;
    }
    
    void SetAutoSwitchOn(BOOL32 bOn)
    {
        m_bAutoSwitchOn = bOn;
    }

    BOOL32 GetAutoSwitchOn()
    {
        return m_bAutoSwitchOn;
    }

}TAutoswitchReq, *PTAutoswitchReq;

typedef struct tagAutoswitchRsp: public TRsp{}TAutoswitchRsp, PTAutoswitchRsp;

#endif //H323CASCADE_H_ // [8/13/2010 xliang] 


#ifdef WIN32
#pragma pack(1)
#define PACKED 
#endif // WIN32


// �ն˵�ַ��Ϣ

// ��ַ����
#define		ADDR_TYPE_IP		1
#define		ADDR_TYPE_ALIAS		2
// // 
// ��������
#define		ALIAS_H323ID		1
#define		ALIAS_E164			2
#define		ALIAS_EMAIL			3

typedef struct tagTerAddr
{
public :
	u8 GetAddrType( void ) { return byAddrType; }
	void SetAddrType( u8 byType ) { byAddrType = byType; }
	
	void SetIpAddr( u32 ip, u16 port )
	{
		dwIp = ip;
		wPort = htons( port );
	}
	u32 GetIpAddr( void ) { return dwIp; }
	u16 GetIpPort( void ) { return ntohs( wPort ); }

	//add by yj for ipv6
	void SetIpAddr_Ipv6( u8* ipv6, u16 port, s16 scopeID)
	{
		memcpy(dwIp_ipv6, ipv6, sizeof(dwIp_ipv6));
		wPort = htons( port );
        swScopeId = scopeID;
	}
	u8* GetIpAddr_Ipv6( void ) { return dwIp_ipv6; }
	s16 GetScopeId( void ) { return swScopeId; }
	//end

	u8 GetAliasType( void ) { return byAliasType; }
	s8* GetAliasName( void ) { return achAlias; }
	BOOL SetAlias( u8 byType, const s8* pchName, u8 byNameLen ) 
	{ 
		if ( pchName == NULL || byNameLen == 0 )
			return FALSE;
		
		byAliasType = byType; 
		memset( achAlias, 0, sizeof( achAlias ) );
		u8 byLen = min( byNameLen, (u8)VALID_LEN_ALIAS );
		memcpy( achAlias, pchName, byLen );
		achAlias[byLen] = '\0';
		return TRUE;
	}
	
	tagTerAddr() 
	{
		memset( this, 0, sizeof( tagTerAddr ) );
	}
	
	void Reset( void )
	{
		memset( this, 0, sizeof( tagTerAddr ) );
	}
	
private :
	u8	byAddrType;		// ��ַ����
	u32 dwIp;			// IP(������)
	u16	wPort;			// �˿ں�
	u8	byAliasType;	// ��������
	s8 achAlias[ VALID_LEN_ALIAS + 1 ];

	//add by yj for ipv6
    u8	byAddrIpType;		// IP��ַ����
    u8 dwIp_ipv6[IPV6_NAME_LEN];			// IPv6��ַ(��������)
	s16 swScopeId;
	//end
}
#if defined(_VXWORKS_) || (defined(_LINUX_) && !defined(_EQUATOR_))
__attribute__ ((packed)) 
#endif
TTERADDRESS,*PTTERADDRESS;

#ifdef WIN32
#pragma pack()
#endif




//��ʼ��������
BOOL32 MMcuStackInit(u16 wListenPort,BOOL32 bSockInit = FALSE);
//���ʼ��������
BOOL32 MMcuStackClean(BOOL32 bSockClean = FALSE);

//�µĻ��鼶���ɹ�֪ͨ
#define 	H_CASCADE_NEW_CALL_NTF   (s32)CASCADE_MSGTYPE_ENDING  
//���鼶���Ͽ�֪ͨ
#define     H_CASCADE_DROP_CALL_NTF  (s32)(H_CASCADE_NEW_CALL_NTF+1)
API void mmcusetlog(u8 level);
API void mmcuhelp();


///////////////////////////////// Outgoing Interface ////////////////////////////////

/*====================================================================
������      : NotifyNewCallT
����        : �������о��
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: hsCall   - Э��ջ���о��
    		  lphaCall - Ӧ�ó�����о��
����ֵ˵��  : �ɹ� - cb_ok
              ʧ�� - cb_err
====================================================================*/
typedef s32 (KDVCALLBACK* NotifyNewCallT)(HCALL hsCall, LPHAPPCALL lphaCall);
//add by daiqing 20100723 for 460 kdv
/*====================================================================
������      : NotifyNew460CallT
����        : �������о��
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: hsCall   - Э��ջ���о��
    		  lphaCall - Ӧ�ó�����о��
����ֵ˵��  : �ɹ� - cb_ok
              ʧ�� - cb_err
====================================================================*/
typedef s32 (KDVCALLBACK* NotifyNew460CallT)(HCALL hsCall, LPHAPPCALL lphaCall , const void* pBuf , u16 nBufLen );
//end
/*====================================================================
������      : NotifyNewChanT
����        : �����ŵ����
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: haCall - Ӧ�ó�����о��
			  hsCall - Э��ջ���о��
			  hsChan - Э��ջ�ŵ����
			  lphaChan - Ӧ�ó����ŵ����
����ֵ˵��  : �ɹ� - cb_ok
              ʧ�� - cb_err
====================================================================*/
typedef s32 (KDVCALLBACK* NotifyNewChanT)(HAPPCALL haCall,HCALL hsCall,HCHAN hsChan,
										  LPHAPPCHAN lphaChan);

/*====================================================================
������      : NotifyCallCtrlMsgT
����        : ���п���֪ͨ����
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: haCall  - Ӧ�ó�����о��
			  hsCall  - Э��ջ���о��
			  msgType - ��Ϣ����
			  pBuf    - ����������
			  nBufLen - ��������
����ֵ˵��  : �ɹ� - cb_ok
              ʧ�� - cb_err
====================================================================*/
typedef s32 (KDVCALLBACK* NotifyCallCtrlMsgT)(HAPPCALL haCall,HCALL hsCall,u16 msgType,
											  const void* pBuf,u16 nBufLen);

/*====================================================================
������      : NotifyChanCtrlMsgT
����        : �ŵ�����֪ͨ����
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: haCall  - Ӧ�ó�����о��
              hsCall  - Э��ջ���о��
              haChan  - Ӧ�ó����ŵ����
			  hsChan  - Э��ջ�ŵ����
			  msgType - ��Ϣ����
			  pBuf    - ����������
			  nBufLen - ��������
����ֵ˵��  : �ɹ� - cb_ok
              ʧ�� - cb_err
====================================================================*/
typedef s32 (KDVCALLBACK* NotifyChanCtrlMsgT)(HAPPCALL haCall,HCALL hsCall,HAPPCHAN haChan,HCHAN hsChan,
											  u16 msgType,const void* pBuf,u16 nBufLen);

/*====================================================================
������      : NotifyConfCtrlMsgT
����        : �������֪ͨ����
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: haCall  - Ӧ�ó�����о��
			  hsCall  - Э��ջ���о��
			  msgType - ��Ϣ����
			  pBuf    - ����������
			  nBufLen - ��������
����ֵ˵��  : �ɹ� - cb_ok
              ʧ�� - cb_err
====================================================================*/
typedef s32 (KDVCALLBACK* NotifyConfCtrlMsgT)(HAPPCALL haCall, HCALL hsCall,u16 msgType,const void* pBuf,
											  u16 nBufLen);

/*====================================================================
������      : NotifyRasCtrlMsgT
����        : RAS��Ϣ֪ͨ����
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: haCall  - Ӧ�ó�����о��
              hsCall  - Э��ջ���о��
              haRas   - Ӧ�ó���RAS���
			  hsRas   - Э��ջRAS���
			  msgType - ��Ϣ����
			  pBuf    - ����������
			  nBufLen - ��������
����ֵ˵��  : �ɹ� - cb_ok
              ʧ�� - cb_err
====================================================================*/
typedef s32 (KDVCALLBACK* NotifyRasCtrlMsgT)(HAPPCALL haCall,HCALL hsCall,HAPPRAS haRas, HRAS hsRas,u16 msgType,
											 const void* pBuf,u16 nBufLen);

/*====================================================================
������      : NotifyFeccMsgT
����        : H.224, H.281���ܻص�����
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: hsCall     - Э��ջ���о��
              hsChan     - Э��ջ�ŵ����
			  feccStruct - Զң����(TFeccStruct)
			  terSrc     - Դ���ն��б�
			  terDst     - Դ���ն��б�
����ֵ˵��  : �ɹ� - cb_ok
              ʧ�� - cb_err
====================================================================*/
typedef s32 (KDVCALLBACK *NotifyFeccMsgT)(HCALL hsCall, HCHAN hsChan, 
										  TFeccStruct feccStruct,
										  TTERLABEL terSrc, TTERLABEL terDst);

//MMcu ���鼶��������Ϣ�ص�����
typedef int (KDVCALLBACK *NotifyMMcuMsgT)(HAPPCALL haCall,HCALL hsCall,HAPPCHAN haChan,HCHAN hsChan,
                                          u16 msgType,const void* pBuf,u16 nBufLen);


//�ص�����ָ��ṹ
typedef struct 
{
    NotifyNewCallT		fpNewCall;
    NotifyNewChanT		fpNewChan;
    NotifyCallCtrlMsgT  fpCallCtrlMsg;
    NotifyChanCtrlMsgT  fpChanCtrlMsg;
    NotifyConfCtrlMsgT	fpConfCtrlMsg;
    NotifyRasCtrlMsgT	fpRasCtrlMsg;
    NotifyFeccMsgT      fpFeccMsg;  
    NotifyMMcuMsgT      fpMMcuMsg;    
	//add by daiqing 20100723 for 460 kdv
	NotifyNew460CallT   fpNew460Call;
	//end
}H323EVENT,*LPH323EVENT;

///////////////////////////////// Incoming Interface ////////////////////////////////

/*====================================================================
��	 ��   ��: kdvInitH323Adapter
��	      ��: ��ʼ��H323����ģ��
�� �� ʵ  ��: 
����ȫ�ֱ���: g_hApp
�������˵��: sConfigFile(IN), Э��ջ�����ļ���
              keyParams(INOUT), Э��ջ�ؼ����ò���:
	        1> �������ļ���ʼ��ʧ��ʱ��������Щ������ʼ��Э��ջ
			2> �������ļ���ʼ���ɹ�ʱ���������ļ���ȡһЩ�������ýṹ�У��Ա�����
			  
��   ��   ֵ: �ɹ� - &g_hApp
			  ʧ�� - NULL		
====================================================================*/
void*  kdvInitH323Adapter(IN s8* sConfigFile, IN TH323CONFIG *keyParams = NULL);

/*====================================================================
��	 ��   ��: kdvSetStackAdditionalConfig
��	      ��: ����Э��ջ����
�� �� ʵ  ��: 
����ȫ�ֱ���: 
�������˵��: ptStackConfig   - Э��ջ����
��   ��   ֵ: �ɹ� - act_ok
ʧ�� - act_err
====================================================================*/
s32 kdvSetStackAdditionalConfig(IN TAdditionalConfig* ptStackConfig);

/*====================================================================
��	 ��   ��: kdvCloseH323Adapter
��	      ��: �ر�H323����ģ��
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: ��
��   ��   ֵ: ��
====================================================================*/
void kdvCloseH323Adapter();

/*====================================================================
��	 ��   ��: kdvSetAppCallBack
��	      ��: ע��Ӧ�ûص�����
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: lpEvent - �ص������ṹָ��
��   ��   ֵ: �ɹ� - act_ok
			  ʧ�� - act_err
====================================================================*/
s32  kdvSetAppCallBack(IN LPH323EVENT lpEvent);

/*====================================================================
��	 ��   ��: kdvCheckMessage
��	      ��: ���Э��ջ�Ƿ��յ�H.323��Ϣ
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: 
��   ��   ֵ: 
====================================================================*/
void kdvCheckMessage();

/*====================================================================
��	 ��   ��: kdvCreateNewCall
��	      ��: �����µĺ��У������ڷ��ͺ�����Ϣǰ����,�����ȴ����ٺ���
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�� �� ��  ��: haCall -   Ӧ�ó�����о��
�� �� ��  ��: lphsCall - Э��ջ���о��
��   ��   ֵ: �ɹ� - act_ok
              ʧ�� - act_err
====================================================================*/
s32 kdvCreateNewCall(IN HAPPCALL haCall, OUT LPHCALL lphsCall, IN bool bSync = true);

/*====================================================================
��	 ��   ��: kdvCreateNewChan
��	      ��: �����µĺ��У������ڷ����ŵ���Ϣǰ����,�����ȴ����ٲ���
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�� �� ��  ��: hsCall -   Э��ջ���о��
			  haChan -   Ӧ�ó����ŵ����
�� �� ��  ��: lphsCall - Э��ջ�ŵ����
��   ��   ֵ: �ɹ� - act_ok
              ʧ�� - act_err
====================================================================*/
s32 kdvCreateNewChan(IN HCALL hsCall, IN HAPPCHAN haChan, 
                     OUT LPHCHAN lphsChan, IN bool bSync = true);

/*====================================================================
��	 ��   ��: kdvCreateRASStartTransaction
��	      ��: ����RAS��Transaction�������ȴ����ٲ���
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�� �� ��  ��: haRas       -   Ӧ�ó���RAS���
              transaction -   RAS�¼�����
              destAddress -   �����ն���GK��ַ������GK���ն˵�ַ
              hsCall      -   Э��ջ���о��
�� �� ��  ��: lphsRas -  Э��ջRAS���
��   ��   ֵ: �ɹ� - act_ok
ʧ�� - act_err
====================================================================*/
s32 kdvCreateRASStartTransaction(IN  HAPPRAS          haRas,
                                 OUT LPHRAS           lphsRas,
                                 IN  cmRASTransaction transaction,
                                 IN  TNETADDR*        destAddress,
                                 IN  HCALL            hsCall,
                                 IN  bool             bSync = true);

/*====================================================================
��	 ��   ��: kdvSendRasCtrlMsg
��	      ��: ����RAS������Ϣ
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: hsCall  - ���о��
              hsRas   - RAS���
              msgType - ��Ϣ����
			  pBuf    - ����������
			  nBufLen - ��������
��   ��   ֵ: �ɹ� - act_ok
              ʧ�� - act_err
====================================================================*/
s32 kdvSendRasCtrlMsg(IN HCALL hsCall, IN HRAS hsRas, IN u16 msgType,
                      IN const void* pBuf, IN u16 nBufLen, IN bool bSync = true);

/*====================================================================
��	 ��   ��: kdvSendCallCtrlMsg
��	      ��: ���ͺ��п�����Ϣ
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: hsCall  - ���о��
              msgType - ��Ϣ����
			  pBuf    - ����������
			  nBufLen - ��������
��   ��   ֵ: �ɹ� - act_ok
              ʧ�� - act_err
====================================================================*/
s32 kdvSendCallCtrlMsg(IN HCALL hsCall,IN u16 msgType,
                       IN const void* pBuf, IN u16 nBufLen, IN bool bSync = true);

/*====================================================================
��	 ��   ��: kdvSendChanCtrlMsg
��	      ��: �����ŵ�������Ϣ
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: hsChan  - �ŵ����
              msgType - ��Ϣ����
			  pBuf    - ����������
			  nBufLen - ��������
��   ��   ֵ: �ɹ� - act_ok
              ʧ�� - act_err
====================================================================*/
s32 kdvSendChanCtrlMsg(IN HCHAN hsChan, IN u16 msgType,
                       IN const void* pBuf,IN u16 nBufLen, IN bool bSync = true);

/*====================================================================
��	 ��   ��: kdvSendConfCtrlMsg
��	      ��: ���ͻ��������Ϣ
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: hsCall  - ���о��
              msgType - ��Ϣ����
			  pBuf    - ����������
			  nBufLen - ��������
��   ��   ֵ: �ɹ� - act_ok
              ʧ�� - act_err
====================================================================*/
s32 kdvSendConfCtrlMsg(IN HCALL hsCall, IN u16 msgType,
                       IN const void* pBuf, IN u16 nBufLen, IN bool bSync = true);

/*====================================================================
��	 ��   ��: kdvCheckValid
��	      ��: �����о���ĺϷ���
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: hsCall	- ���о��
�������˵����
��   ��   ֵ: FALSE - ��Ч
              TRUE  - ��Ч
====================================================================*/
BOOL kdvCheckValid(IN HCALL hsCall);

/*====================================================================
��	 ��   ��: kdvCheckValid
��	      ��: ���ͨ������ĺϷ���
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: hsChan    - ͨ�����
�������˵����
��   ��   ֵ: FALSE - ��Ч
              TRUE  - ��Ч
====================================================================*/
BOOL kdvCheckValid(IN HCHAN hsChan);

/*====================================================================
��	 ��   ��: kdvCallSetHandle
��	      ��: ����hsCall��Ӧ�ò���
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: hsCall - Э��ջ���о��
              haCall - Ӧ�þ��
			  bSync  - �Ƿ�ͬ��
��   ��   ֵ: �ɹ� - act_ok
              ʧ�� - act_err
====================================================================*/
s32 kdvCallSetHandle(IN HCALL hsCall, IN HAPPCALL haCall, IN bool bSync = true);

/*====================================================================
��	 ��   ��: kdvCallGetHandle
��	      ��: ���Ӧ�þ��
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: hsCall - Э��ջ���о��              
			  bSync  - �Ƿ�ͬ��
�������˵��: haCall - Ӧ�þ��
��   ��   ֵ: �ɹ� - act_ok
              ʧ�� - act_err
====================================================================*/
s32 kdvCallGetHandle(IN HCALL hsCall, OUT HAPPCALL* haCall, IN bool bSync = true);

/*====================================================================
��	 ��   ��: kdvRasUpdateRegAliasList
��	      ��: ���±��˱���
�� �� ʵ  ��: 
����ȫ�ֱ���: g_hApp
�������˵��: alias  - ��������
			  size	 - ��������              
��   ��   ֵ: �ɹ�   - act_ok
              ʧ��   - act_err
====================================================================*/
s32 kdvRasUpdateRegAliasList(IN cmAlias alias[], IN s32 size);

/*====================================================================
��	 ��   ��: kdvSetGKRASAddress
��	      ��: ����gk��ַ
�� �� ʵ  ��: 
����ȫ�ֱ���: 
�������˵��: hApp - HAPP
              tr   - GK��ַ              
��   ��   ֵ: �ɹ� - act_ok
              ʧ�� - act_err
====================================================================*/
s32 kdvSetGKRASAddress(IN HAPP hApp, IN cmTransportAddress tr, bool bSync = true );

/*====================================================================
��	 ��   ��: kdvGetCallParam
��	      ��: ��ú��в���
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: hsCall	- ���о��
			  cpt		- ���в�������
			  bSync		- �Ƿ�ͬ��
�������˵����pBuf		- ����ֵ
			  nBufLen	- ��������
��   ��   ֵ: �ɹ� - act_ok
              ʧ�� - act_err
====================================================================*/
s32 kdvGetCallParam(IN HCALL hsCall, IN CallParamType cpt, 
                    OUT void* pBuf, OUT u16 nBufLen, IN bool bSync = true);

/*====================================================================
��	 ��   ��: kdvIsMasterCall
��	      ��: ����Ƿ�����
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: hsCall    - ���о��
�������˵����
��   ��   ֵ: FALSE - ����
              TRUE  - ����
====================================================================*/
BOOL kdvIsMasterCall(IN HCALL hsCall);

/*====================================================================
��	 ��   ��: kdvIsMasterTerminal
��	      ��: ������Ӿ����Ľ���Ƿ�master
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: hsCall    - ���о��
�������˵����
��   ��   ֵ: FALSE - slave
              TRUE  - master
====================================================================*/
BOOL kdvIsMasterTerminal(IN HCALL hsCall);

/*====================================================================
��	 ��   ��: kdvGetLocalCallIPAddress
��	      ��: ��ȡ���˺��е���ʵIP
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: hsCall    - ���о��
�������˵����
��   ��   ֵ: �������IP��ַ
====================================================================*/
#if ( RV_H323_TRANSPORT_ADDRESS == RV_H323_TRANSPORT_ADDRESS_ANY)
ipAddress kdvGetLocalCallIPAddress(IN HCALL hsCall);
#elif ( RV_H323_TRANSPORT_ADDRESS == RV_H323_TRANSPORT_ADDRESS_OLD)
u32 kdvGetLocalCallIPAddress(HCALL hsCall);
#endif


/*====================================================================
��	 ��   ��: GetEType
��	      ��: ��ͨ�غ�����ת���ɴ�������Ϣ���غ�����
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: wType	    - ��ת�����غ�����
              byEBits   - ��λ�ļ���λ���� emEncryptTypeDES|emEncryptTypeAES   
��   ��   ֵ: ת������غ�����
====================================================================*/
inline u16 GetEType( IN u16 wType, IN u8 byEBits) 
{
	u16 wTmp = byEBits;
	wTmp = ((wTmp<<8)&0xff00);
    wTmp |= wType;
	return wTmp;
};

inline u16 GetH239Type( IN u16 wType ) 
{
    return GetEType(wType, emEncryptTypeH239);
};

inline BOOL IsH239Type( IN u16 wType )
{  
    return ((wType>>8) & emEncryptTypeH239);
}

/*====================================================================
��	 ��   ��: IsAudioType
��	      ��: �ж��Ƿ���Ƶ����
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: wPayLoadType	 - �غ�����
��   ��   ֵ: �ɹ� - ����0
              ʧ�� - С��0
====================================================================*/
inline BOOL IsAudioType(IN u16 wPayLoadType)
{
	return PayloardIsAudioType(wPayLoadType); 
}

/*====================================================================
��	 ��   ��: IsVideoType
��	      ��: �ж��Ƿ���Ƶ����
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: wPayLoadType	 - �غ�����
��   ��   ֵ: �ɹ� - ����0
              ʧ�� - С��0
====================================================================*/
inline BOOL IsVideoType(IN u16 wPayLoadType)
{
	return PayloardIsVideoType(wPayLoadType);
}

/*====================================================================
��	 ��   ��: IsDataType
��	      ��: �ж��Ƿ���������
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: wPayLoadType	 - �غ�����
��   ��   ֵ: �ɹ� - ����0
              ʧ�� - С��0
====================================================================*/
inline BOOL IsDataType(IN u16 wPayLoadType)
{
	return PayloardIsDataType(wPayLoadType);
}


/////////////////////////////H323 Annex Q/////////////////////////////////

/*====================================================================
��	 ��   ��: kdvFeccBind
��	      ��: �������а�Զң���󣬵�Ե����ʱ�����
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: hsChan	 - h224ͨ�����
              localTer   - �����ն��б�(TTERLABEL)
			  remoteTer  - Զ���ն��б�(TTERLABEL)
��   ��   ֵ: �ɹ� - ����0
              ʧ�� - С��0
====================================================================*/
 s32 kdvFeccBind(IN HCHAN hsChan, IN TTERLABEL localTer, 
                 IN TTERLABEL remoteTer, IN bool bSync = true);

/*====================================================================
��	 ��   ��: kdvSendFeccMsg
��	      ��: ͨ��h224ͨ������Զң����
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: hsChan	 - h224ͨ�����
			  feccStruct - Զң����(TFeccStruct)
��   ��   ֵ: �ɹ� - ����0
              ʧ�� - С��0
====================================================================*/
s32 kdvSendFeccMsg(IN HCHAN hsChan, IN TFeccStruct feccStruct, IN bool bSync = true);


/* ����й�Э��ջ�ĺ������������ź������� */
s32 kdvCmCallGetParam(IN HCALL hsCall, IN cmCallParam param, IN s32 index,
                      INOUT s32* value, OUT s8* svalue, IN bool bSync = true);

s32 kdvCmRASStartTransaction(IN  HAPP hApp, IN  HAPPRAS haRas, OUT LPHRAS lphsRas,
                             IN  cmRASTransaction transaction, IN cmRASTransport* destAddress,
                             IN  HCALL hsCall, IN  bool bSync = true);

s32 kdvCmRASSetParam(IN HRAS hsRas, IN cmRASTrStage trStage, IN cmRASParam param,
                     IN s32 index, IN s32 value, IN char* svalue, IN bool bSync = true);

s32 kdvCmRASGetParam(IN HRAS hsRas, IN  cmRASTrStage trStage, IN  cmRASParam param,
                     IN s32 index, IN OUT s32* value, /* value or length */
                     IN s8* svalue, IN bool bSync = true);

s32 kdvCmRASRequest(IN  HRAS hsRas, IN  bool bSync = true);

s32 kdvCmRASClose(IN  HRAS hsRas, IN bool bSync = true);

/*====================================================================
��	 ��   ��: kdvRASSetCallAddress
��	      ��: ����ע����е�ַ
�� �� ʵ  ��: 
����ȫ�ֱ���: 
�������˵��: ta   - ���������ַ
��   ��   ֵ: �ɹ� - act_ok
              ʧ�� - act_err
====================================================================*/
s32 kdvRASSetCallAddress(IN HAPP hApp, IN cmTransportAddress tr);

/*====================================================================
��	 ��   ��: kdvSetlocalRASAddress
��	      ��: ����ע��RAS��ַ
�� �� ʵ  ��: 
����ȫ�ֱ���: 
�������˵��: ta   - ����RAS��ַ
��   ��   ֵ: �ɹ� - act_ok
              ʧ�� - act_err
====================================================================*/
s32 kdvSetlocalRASAddress(IN HAPP hApp, IN cmTransportAddress tr);


const s8* GetCmAliasType(AliasType dwAliasType);
const s8* GetCmAliasType(cmAliasType dwAliasType);
const s8* GetCmPayloadString(u16 wSubMsgType);
const s8* GetCmConfMsgString(u16 wSubMsgType);
const s8* GetCmChanMsgString(u16 wSubMsgType);
const s8* GetCmCallMsgString(u16 wPayload);
const s8* GetCmRasMsgString(u16 wSubMsgType);

/*====================================================================
��	 ��   ��: kdvUpdateGatekeeperID
��	      ��: ����GatekeeperID
�� �� ʵ  ��: 
����ȫ�ֱ���: 
�������˵��: tGKID   - gatekeeperid
��   ��   ֵ: �ɹ� - act_ok
ʧ�� - act_err
====================================================================*/
s32 kdvUpdateGatekeeperID(IN HAPP hApp, IN cmAlias tGKID);

//���ڼ���
BOOL GetDesDHKey(HCALL hsCall, u8 **pBuf, s32 *pnBits);
BOOL GetAesDHKey(HCALL hsCall, u8 **pBuf, s32 *pnBits);


//���ͻ��鼶��������Ϣ
int kdvSendMMcuCtrlMsg(HCHAN hsChan,u16 msgType,const void* pBuf,u16 nBufLen,bool bSync = true);

/**˵��***********************************************************************
*
1.����˫���߼�ͨ��(����Э��ͨ��)(I incoming, O out )
> �߼�ͨ����ͻʱ�� master �ն˾ܾ�incoming channel
> I ����������tcp connectʱ��ack��Ϣ���������Э��ͨ��������ַ
> O ������ack���е���Э��ͨ��������ַ����Iû������tcp connectʱ,����tcp connect
2.����ͨ��
>h_chan_open,h_chan_openAck ֻ����дpayload, m_tRtp.ip.
*
******************************************************************************/

/************************** DNS Trans *****************************************/
typedef enum
{
    DNS_SUCCESS = 0,
    DNS_TIMEOUT,
    DNS_NOTFOUND,
    DNS_FAILED,
} dnsResult;

typedef s32 (*DnsCallBackT)(s32 nUserID, dnsResult eResult, s32 nIpNum, u32* adwIP);

API int kdvDnsRequest(s8* pchName, u32 dwDnsServer, u32 dwUserID, 
                      DnsCallBackT ptDnsCallbackFunc, IN  BOOL32 bSync);

/******************************************************************************/

//����IRR��Ϣ�����ڲ�����HCALL�ĳ��ϣ������á�
s32 kdvSetRasIRR(HRAS hsRas, TIRRINFO* ptIRRInfo, bool bSync);

//��Ϣ�����������������ת��
s32 kdvH323Adapterhton(u16 msgType, void* pBuf, u16 nBufLen, BOOL bhton);

//����H323TOSֵ
API s32 kdvSetH323TOS(IN s32 nTOS, IN bool bSync = true);
//��ȡH323TOSֵ
API s32 kdvGetH323TOS();

//����ԶңTOSֵ, ��������kdvdatanet���ж���
API s32 kdvSetDataTOS(s32 nTOS);
API s32 kdvGetDataTOS();

API s8* GetPeerVersionID(HCALL hsCall);
API s8* GetPeerProductID(HCALL hsCall);
API BOOL IsPeerSupportNewG7221c(HCALL hsCall);  //�Զ��Ƿ�֧����ȷ�ֽ����G7221C��Ƶ����

void KdvSetIsH460GW(BOOL32 bIsGw);

int KdvSendTpktPinhole(HCALL hsCall, cmTpktChanHandleType type, BOOL bSync = TRUE);
void KdvSetH460Config(BOOL bSupportH460, BOOL bMediaTraversalServer, BOOL bSupportTransMultiMedia);
void KdvSetCallApplicationHandle(HCALL hsCall, void* haCall);

// ���ñ����Ƿ�ΪUTF8����
API void kdvSetLocalIsUTF8(BOOL32 bIsUtf8);


//debug print
API void kdv323help();
API void set323trace(u8 byLevel);
API void setstacklog(s32 nLevel, BOOL bFileLogOn);
API void setfecctype(u8 byType);
API void seth323print(s32 nType, u8 byDir);
API void print323call();
API void print323config();
API void pne();

API void radvaltree();//[20120619]
API void radallnode( BOOL bJustRootNode );//[20120918]
// API void printrasstatus();
// API void printcallstatus();
// API void printtransstatus();
// API void printpoolstatus();
API void watchdog();
API void ospprintstack();
BOOL32 kdvCloseCall(HCALL hCall);

#endif //_H323ADAPTER_H
