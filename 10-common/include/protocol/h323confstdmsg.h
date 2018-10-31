#ifndef _H323CONFSTDMSG_H
#define _H323CONFSTDMSG_H


enum H245CtrlMsgType 
{
	/************************h.245 Standard**************************/
	h_ctrl_MultipointConference				= 7,      //��ʼ������ָʾ  MC->ter, Master->slave,   [incoming]&[outgoing]: NULL
	h_ctrl_CancelMultipointConference		= 8,      //ȡ��������ָʾ  MC->ter, Master->slave,   [outgoing]: NULL
		
	h_ctrl_communicationModeCommand			= 9,      //����ģʽ����	    MC->ter,   [incoming]&[outgoing]: [TCOMMODEINFO[]],Ŀǰ��ʹ��
	//10	
	h_ctrl_enterH243Password				= 10,	  //MCѯ�ʻ�������    MC->ter,   [incoming]&[outgoing]: NULL
	h_ctrl_passwordResponse					= 11,	  //�ն˻ش�����	    ter->MC,   [incoming]&[outgoing]: [TPassRsp]
	h_ctrl_terminalNumberAssign				= 12,     //�����ն˱��	    MC->ter,   [incoming]&[outgoing]: [TTERLABEL]
	h_ctrl_terminalListRequest				= 13,     //�����ն��б�	    ter->MC,   [incoming]&[outgoing]: NULL			
	h_ctrl_terminalListResponse				= 14,     //�ش��ն��б�	    MC->ter,   [incoming]&[outgoing]: [TTERLABEL[]]
	h_ctrl_requestTerminalID				= 15,     //terѯ���ն���	    ter->MC,   [incoming]&[outgoing]: [TTERLABEL]
	h_ctrl_mCTerminalIDResponse				= 16,     //MC�ش��ն���	    MC->ter,   [incoming]&[outgoing]: [TTERINFO]
	h_ctrl_enterH243TerminalID				= 17,	  //MCѯ���ն���	    MC->ter,   [incoming]&[outgoing]: NULL
	h_ctrl_terminalIDResponse				= 18,     //ter�ش��ն���	    ter->MC,   [incoming]&[outgoing]: [TTERINFO]
	h_ctrl_requestAllTerminalIDs			= 19,     //ter���������ն��� ter->MC,   [incoming]&[outgoing]: NULL
	h_ctrl_requestAllTerminalIDsResponse	= 20,     //�ش������ն�����	MC->ter,   [incoming]&[outgoing]: [TTERINFO[]]
	h_ctrl_terminalJoinedConference			= 21,     //�ն˼������		MC->ter,   [incoming]&[outgoing]: [TTERLABEL]
	h_ctrl_terminalLeftConference			= 22,     //�ն��˳�����		MC->ter,   [incoming]&[outgoing]: [TTERLABEL]
	h_ctrl_dropTerminal						= 23,     //ǿ���ն��˳�		chair->MC, [incoming]&[outgoing]: [TTERLABEL]
	h_ctrl_terminalDropReject				= 24,     //ǿ���ն��˳�ʧ��	MC->chair, [incoming]&[outgoing]: NULL	
	h_ctrl_dropConference					= 25,     //�������� chair->MC,MC->ter,  [incoming]&[outgoing]: NULL
	//26
	h_ctrl_requestForFloor					= 26,     //���뷢��			ter->MC,   [incoming]&[outgoing]: NULL
	h_ctrl_floorRequested					= 27,     //��������			MC->chair, [incoming]&[outgoing]: [TTERLABEL]
	h_ctrl_makeTerminalBroadcaster			= 28,     //�㲥�ն�			chair->MC, [incoming]&[outgoing]: [TTERLABEL+u8:CtrlMode]
	h_ctrl_makeTerminalBroadcasterResponse	= 29,	  //�㲥Ӧ��			MC->chair, [incoming]&[outgoing]: [u8:CtrlResult]
	h_ctrl_cancelMakeTerminalBroadcaster	= 30,	  //ȡ���㲥			chair->MC, [incoming]&[outgoing]: NULL
	h_ctrl_seenByAll						= 31,     //�㲥Դָʾ		MC->ter,   [incoming]&[outgoing]: NULL
	h_ctrl_cancelSeenByAll					= 32,     //�㲥Դ��ȡ��ָʾ	MC->ter,   [incoming]&[outgoing]: NULL
	h_ctrl_seenByAtLeastOneOther			= 33,     //��֪�������ն�ѡ��  MC->ter, [incoming]&[outgoing]: NULL
	h_ctrl_cancelSeenByAtLeastOneOther		= 34,     //��֪�������ն�ͣ��  MC->ter, [incoming]&[outgoing]: NULL
	h_ctrl_sendThisSource					= 35,     //ѡ���ն�			chair->MC, [incoming]&[outgoing]: [TTERLABEL+u8:CtrlMode]
	h_ctrl_sendThisSourceResponse			= 36,     //ѡ��Ӧ��			MC->chair, [incoming]&[outgoing]: [u8:CtrlResult]
	h_ctrl_cancelSendThisSource				= 37,     //ȡ��ѡ��			chair->MC, [incoming]&[outgoing]: NULL
	h_ctrl_terminalYouAreSeeing				= 38,     //���ڹۿ�����ƵԴ	MC->ter,   [incoming]&[outgoing]: [TTERLABEL]
	//39
	h_ctrl_makeMeChair						= 39,     //������ϯ			ter->MC,   [incoming]&[outgoing]: NULL
	h_ctrl_cancelMakeMeChair				= 40,     //�ͷ���ϯ			chair->MC, [incoming]&[outgoing]: NULL
	h_ctrl_makeMeChairResponse				= 41,     //��ϯ����/�ͷ�Ӧ��	MC->ter,   [incoming]&[outgoing]: [u8:CtrlResult]
	h_ctrl_withdrawChairToken				= 42,     //��ϯ����ָʾ		MC->ter,   [incoming]&[outgoing]: NULL
	h_ctrl_requestChairTokenOwner			= 43,     //ѯ�ʵ�ǰ��ϯ		ter->MC,   [incoming]&[outgoing]: NULL
	h_ctrl_chairTokenOwnerResponse			= 44,     //�ش�ǰ��ϯ		MC->ter,   [incoming]&[outgoing]: [TTERINFO]
	h_ctrl_mcLocationIndication				= 45,	  //����MC��ʵ���ַ	MC->ter,   [incoming]&[outgoing]: [TNETADDR]
	h_ctrl_roundTripDelay					= 46,	  //���Զ��Ƿ�Alive ter->MC,MC->ter, [incoming]&[outgoing]: [s32:nMaxDelay]
	//47   
	h_ctrl_H239Message						= 47,     //����H239��Ϣ      ter->MC,MC->ter, [incoming]&[outgoing]: [TH239INFO]
	h_ctrl_userInput						= 48,     //����UserInput��Ϣ            [incoming]&[outgoing]: [TUserInputInfo]
		
	h_ctrl_roundTripDelay_request			= 49,     //h_ctrl_roundTripDelay����ĸ�����Ϣ(����ǽ�ڲ�ʹ�ã��������������Ӧ��)
		
	h_ctrl_customFecc						= 50,	  //FECC��Ϣ��ʹ��H245����FECC��Ϣ�Ĵ��ݣ���Ҫ����pxy��
		
	h_ctrl_multiplexCapability				= 51,     //multiplexCapability��Ϣ,  [incoming]&[outgoing]: [TMultiplexCapability]
		
	h_ctrl_masterSlaveResponse				= 52,     //[outgoing]      ���Ӿ���response��buf=BOOL32 �����յ��Է�masterslaveresquest���ֶ��ظ��Է�ack
	h_ctrl_OutgoingMultipointConference		= 53,	  //[outgoing]		ת��h_ctrl_MultipointConference��Ϣ���������ر�
		
		
	h_ctrl_standardend						= 100,
		
};

#endif //_H323CONFSTDMSG_H
