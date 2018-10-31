#ifndef _H323CALLSTDMSG_H
#define _H323CALLSTDMSG_H


//������Ϣ
enum H225CallMsgType 
{
	h_call_invalidInterface = 0,
    h_call_make             = 1,	   //�������	      [outgoing]: TCALLPARAM
	h_call_incoming         = 2,	   //���е���		  [incoming]: TCALLPARAM + VendorProductId		  	  	
	h_call_answer		    = 3,       //����(�ܾ�)����   [outgoing]: TNODEINFO
	h_call_drop             = 4,       //��������		  [outgoing]: 1 byte,reason(��׼��Ϣһ��u8���Ǳ���u8+u8)
	h_call_connected        = 5,       //���н���		  [incoming]: TNODEINFO	
	h_call_disconnected     = 6,       //���жϿ�		  [incoming]: 1 byte,reason	
	h_call_facility         = 7,			    //������չ����	  [incoming]&[outgoing]: TFACILITYINFO   
	h_call_h460make         = 8,		        //����h460����	  [outgoing]: TH460CALLPARAM
	//add by daiqing 20100723 for 460 kdv
	h_call_h460CallerMake   = 9,			//�����ն��յ�facility������� [outgoing]: TCALLPARAM
	//end
    //Jacky Wei add h_call_alerting event for KDV1000
    h_call_alerting         = 10,                //Useless except for KDV1000 processes
};

//RAS��Ϣ
enum H225RasMsgType 
{
	h_ras_invalidInterface = 0,
	h_ras_GRQ			   = 1,		//reserve
	h_ras_GCF			   = 2,		//reserve
	h_ras_GRJ              = 3,		//reserve
	h_ras_RRQ              = 4,     //[incoming]&[outgoing]:[TRRQINFO]
	h_ras_RCF			   = 5,		//[incoming]&[outgoing]:[TRCFINFO]    
	h_ras_RRJ              = 6,     //[incoming]&[outgoing]:[int:reason]
	h_ras_LWRRQ            = 7,     //[incoming]&[outgoing]:[TRRQINFO]
	h_ras_ARQ			   = 8,		//[incoming]&[outgoing]:[HCALL][TARQINFO]
	h_ras_ACF              = 9,     //[incoming]&[outgoing]:[HCALL][TACFINFO]
	h_ras_ARJ              = 10,    //[incoming]&[outgoing]:[HCALL][int:reason]
	h_ras_DRQ              = 11,    //[incoming]&[outgoing]:[HCALL][TDRQINFO]
	h_ras_DCF			   = 12,	//[incoming]&[outgoing]:[HCALL][TDCFINFO]
	h_ras_DRJ			   = 13,	//[incoming]&[outgoing]:[HCALL][int:reason]
	h_ras_URQ			   = 14,	//[incoming]&[outgoing]:[TURQINFO]
	h_ras_UCF			   = 15,	//[incoming]&[outgoing]:[TUCFINFO]
	h_ras_URJ			   = 16,	//[incoming]&[outgoing]:[int:reason]
	h_ras_IRQ              = 17,    //[incoming]&[outgoing]:[HCALL][TIRQINFO]
	h_ras_IRQTimeOut       = 18,    //[incoming]:           [HCALL]
	h_ras_IRR			   = 19,	//[incoming]&[outgoing]:[HCALL][TIRRINFO]
	h_ras_BRQ			   = 20,	//[incoming]&[outgoing]:[HCALL][TBRQINFO] 
	h_ras_BCF              = 21,    //[incoming]&[outgoing]:[HCALL][TBCFINFO]
	h_ras_BRJ			   = 22,	//[incoming]&[outgoing]:[HCALL][int:reason]
	h_ras_LRQ			   = 23,	//[incoming]&[outgoing]:[TLRQINFO]
	h_ras_LCF              = 24,    //[incoming]&[outgoing]:[TLCFINFO]
	h_ras_LRJ              = 25,    //[incoming]&[outgoing]:[int:reason]

	h_ras_registration     = 26,	//�Զ�RAS�޸�ע����Ϣ������GKע��	[outgoing]:TRRQINFO
	h_ras_unregistration   = 27,	//�Զ�RAS��GKע��				    [outgoing]:NULL
	h_ras_online		   = 28,	//�Զ�RAS��GKע��ɹ�			    [incoming]:NULL
	h_ras_offline		   = 29,	//�Զ�RASδ��GKע��			        [incoming]:NULL

	h_ras_NSM              = 30,    //�Ǳ���Ϣ
	//add by daiqing 20100720 for 460
	h_ras_SCI              = 31,    //[incoming]&[outgoing]:[TSCIINFO]
//	h_ras_SCR              = 32,    //[incoming]&[outgoing]:[s32] //adapter�յ�SCI��Ϣ����Զ��ظ�SCR��ҵ������ô˷����ˡ�

	h_ras_manual_NSM	   = 33,	//�ֶ�RAS �Ǳ���Ϣ [20121018]
};

//�߼�ͨ����Ϣ
enum H245ChanMsgType 
{
	h_chan_invalidInterface				= 0,
   	 h_chan_open   						= 1,		//[incoming]&[outgoing]: [NULL]&[TCHANPARAM] ���߼�ͨ��
	h_chan_openAck						= 2,		//[incoming]           : [TCHANPARAM]        ͬ����߼�ͨ��
	h_chan_openReject					= 3,		//[outgoing]           : [emlogChannelRejectCause]     �ܾ����߼�ͨ��
	h_chan_connected					= 4,		//[incoming]           : NULL                �ŵ��ѽ���
	h_chan_close						= 5,		//[outgoing][incoming] : NULL                �ر��߼�ͨ��	
	h_chan_parameter					= 6,		//[incoming]	       : [TCHANPARAM]        �õ��߼��ŵ�ý������������ŵ���ַ
	h_chan_remoteRtpAddress				= 7,		//[incoming]           : [TNETADDR]          �õ��Զ�RTP��ַ 
	h_chan_remoteRtcpAddress			= 8,		//[incoming]           : [TNETADDR]          �õ��Զ�RTCP��ַ
	h_chan_dynamicpayloadtype			= 9,		//[incoming]           : [u8]                �õ�ͨ���Ķ�̬�غ�����    
	h_chan_VideoFreezePicture			= 10,		//[incoming]&[outgoing]: [NULL]&[NULL]       ͼ�񶳽�����
	h_chan_videofastupdatePIC			= 11,		//[incoming]&[outgoing]: [NULL]&[NULL]       ͼ���������
	h_chan_videofastupdateGOB			= 12,		//[incoming]&[outgoing]: [TVFUGOB]&[TVFUGOB] GOB��������
	h_chan_videofastupdateMB			= 13,		//[incoming]&[outgoing]: [TVFUMB]&[TVFUMB]   MB��������
	h_chan_VideoSendSyncEveryGOB		= 14,		//[incoming]&[outgoing]: [NULL]&[NULL]       use sync for every GOB as defined in H.263
	h_chan_VideoSendSyncEveryGOBCancel	= 15,		//[incoming]&[outgoing]: [NULL]&[NULL]       cancel use sync for every GOB as defined in H.263
    h_chan_SwitchReceiveMediaOn         = 16,		//[incoming]&[outgoing]: [NULL]&[NULL]       logical channel should be used for receive
	h_chan_SwitchReceiveMediaOff        = 17,		//[incoming]&[outgoing]: [NULL]&[NULL]       logical channel should not be used for receive
	h_chan_tsto							= 18,		//[incoming]&[outgoing]: [TTSTO]             temporal spatial tradeoff operation.
	h_chan_flowControl					= 19,		//[incoming]&[outgoing]: [u16:rate(kbps)]    ������������

	h_chan_on							= 20,		//[incoming]&[outgoing]: [NULL]&[NULL]       �����߼�ͨ����    ��ʼ��������    
	h_chan_off							= 21,		//[incoming]&[outgoing]: [NULL]&[NULL]       �����߼�ͨ����    ֹͣ��������

	h_chan_MediaLoopRequest				= 22,		//[incoming]: [HCHAN]
	h_chan_MediaLoopConfirm				= 23,		//[incoming]: [HCHAN]
	h_chan_MediaLoopReject				= 24,		//[incoming]: [HCHAN]
	h_chan_MediaLoopOff					= 25,		//[incoming]: [HCALL]
	h_chan_EncryptSyn                   = 26,		//[incoming]: [TEncryptSync]
	h_chan_EncryptionUpdateRequest      = 27,		//[incoming]: [HCHAN]
	h_chan_EncryptionUpdateCommand      = 28,		//[incoming]: [HCHAN][TEncryptSync]

    h_chan_flowControlIndication   		= 29,		//[incoming]&[outgoing]: [u16:rate(kbps)]    ��������ָʾ
	h_chan_keepAliveAddress				= 30,		//[incoming]           : [TNETADDR]          �õ��Զ�keepAlive��ַadded by wangxiaoyi for h460 keepalivechannel
	h_chan_newchan						= 31,	    //[incoming]           : [HCHAN]          OnNewChan����Ϣ
};

//��h245CtrlMsgType����ȡ����
enum H323CapsetCtrlMsgType 
{
	h_ctrl_invlaidInterface				= 0,
	h_ctrl_h245TransportConnected		= 1,         //[incoming]	       :[NULL]	       h245ͨ���ոս���, ��ʱ���Կ�ʼ��������������ȷ��
	h_ctrl_h245Established				= 2,		 //[incoming]		   :[NULL]		   ��������������ȷ�����,���Կ�ʼ���߼�ͨ�����յ�CancelMultipointConference Ҳ�ᷢ����Ϣ 
	h_ctrl_masterSlave					= 3,		 //[incoming]		   :[u8:result]	   ���Ӿ���ack, [incoming]--result��ʾ�������� 
	h_ctrl_masterSlaveDetermine         = 4,		 //[outgoing]&[incoming]:[s32[2]]       ���Ӿ���request, 4byte(terminal Type�� 50��240) + (optional)4 bytes(random number 0-0xffffff), 
	h_ctrl_capNotifyExt					= 5,         //[incoming]&[outgoing]:[TCapSet]&[TCapSet]  �Զ�����ָʾ
	h_ctrl_capResponse				  	= 6,		 //[incoming]&[outgoing]:[u8: result]         ��������Ӧ
};

#endif //_H323CALLSTDMSG_H
