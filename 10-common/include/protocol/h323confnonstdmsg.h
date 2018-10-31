#ifndef _H323CONFNONSTDMSG_H
#define _H323CONFNONSTDMSG_H

namespace qiye_confnonstd_msg
{
	enum emQiyeConfNsmType
	{
		KDVP_NSM_START_ID                 = 0,
		KDVP_NSM_GETMTLIST_REQ            = (KDVP_NSM_START_ID + 1), //MT ��GK���������ն��б�
		KDVP_NSM_GETMTLIST_RSP            = (KDVP_NSM_START_ID + 2), //�ظ�
		KDVP_NSM_GETTSCATEGORY_REQ        = (KDVP_NSM_START_ID + 3), //MT ��TS��ѯ���ͣ���ҵ������Ӫ��
		KDVP_NSM_GETTSCATEGORY_RSP        = (KDVP_NSM_START_ID + 4), //�ظ�
		KDVP_NSM_DELETE_CALL              = (KDVP_NSM_START_ID + 5), //ɾ�����жԲ���
		KDVP_NSM_CREATECONF_REQ           = (KDVP_NSM_START_ID + 6), //MT->GK������������
		KDVP_NSM_CONFE164_NTF             = (KDVP_NSM_START_ID + 7), //MT->GK��������ظ�����E164��
		KDVP_NSM_CREATECONF_RSP           = (KDVP_NSM_START_ID + 8), //GK->MT��������ظ�
		KDVP_NSM_GETCONFLIST_REQ          = (KDVP_NSM_START_ID + 9), //MT->��ȡ�����б�
		KDVP_NSM_GETCONFLIST_RSP	      = (KDVP_NSM_START_ID + 10), //GK->MT�ظ������б�
		KDVP_NSM_JOINCONF_REQ		      = (KDVP_NSM_START_ID + 11), //MT->GK�μӻ�������
		KDVP_NSM_JOINCONF_RSP		      = (KDVP_NSM_START_ID + 12), //GK->MT�ظ��μӻ�������
		KDVP_NSM_CONFNUM_REQ              = (KDVP_NSM_START_ID + 13), //MT->GK��ȡ������Ϳ��л����� 
		KDVP_NSM_CONFNUM_RSP              = (KDVP_NSM_START_ID + 14), //GK->MT�ظ�������Ϳ��л�����
		KDVP_NSM_GETBOOKLIST_REQ          = (KDVP_NSM_START_ID + 15), //MT->GK��ȡԤԼ�����б�
		KDVP_NSM_GETBOOKLIST_RSP          = (KDVP_NSM_START_ID + 16), //GK->MT����ԤԼ�����б�
		KDVP_NSM_CONFDETAIL_REQ           = (KDVP_NSM_START_ID + 17), //MT_GK��ȡ������ϸ��Ϣ(������д�������)
		KDVP_NSM_CONFDETAIL_RSP           = (KDVP_NSM_START_ID + 18), //GK_MT�ظ�������ϸ��Ϣ
		KDVP_NSM_GETNEWCONFLIST_REQ       = (KDVP_NSM_START_ID + 19), //MT->GK��ȡ��ʱ�����б�
		KDVP_NSM_GETNEWCONFLIST_RSP       = (KDVP_NSM_START_ID + 20),
		KDVP_NSM_TEMPLATECONFLIST_REQ     = (KDVP_NSM_START_ID + 21), //MT_GK��ȡ����ģ���б�
		KDVP_NSM_TEMPLATECONFLIST_RSP     = (KDVP_NSM_START_ID + 22),
		KDVP_NSM_NEWJOINCONF_REQ          = (KDVP_NSM_START_ID + 23),
		KDVP_NSM_NEWCREATECONF_REQ        = (KDVP_NSM_START_ID + 24),
		h_ctrl_videoFrameRateChangeCmd = 222,         /********************<<  (��һ·)��Ƶ����֡�ʵ��� >>*******************
                                             * Mc-->ter
                                             *[��Ϣ��]
                                             *
                                             *    +   u8  ����֡��
                                            */
		h_ctrl_chimeInFailInd = 223,					/********************<<  MT����廰ʧ�� >>*******************
																					* Mc-->ter
																					*[��Ϣ��] ��
																					*
																					*/
		h_ctrl_ModifyConfNameReq = 224,				/********************<<  MT�����޸Ļ������� >>*******************
																						* ter-->Mcu
																						* [��Ϣ��] s8[64+1]  ��������
																						*
																						*/
		h_ctrl_ModifyConfNameRsp = 225,				/********************<<  MT�����޸Ļ������� >>*******************
																					* Mcu-->ter
																					* [��Ϣ��] u8  �ɹ�/ʧ��
																					*
																					*/
		h_ctrl_ModifyConfDurationCmd = 226,			/********************<<  MT�����޸Ļ���ʱ�� >>*******************
																						* ter-->Mcu
																						* [��Ϣ��] u16	ʱ������λ�Ƿ���
																						*
																						*/
		h_ctrl_ModifyConfPwdCmd = 227,				/********************<<  MT�����޸Ļ���������� >>*******************
																					* ter-->Mcu
																					* [��Ϣ��] u8	�Ƿ���� 
																					*          + s8[16+1] �������
																					*
	                                        */
    h_ctrl_requestTerminalInfo = 228,				/********************<<  MT(��ϯ)�������ն���Ϣ >>*******
                                            * ter-->Mcu
                                            * [��Ϣ��] TTERLABEL �ն�ID  ���� byMcuNo = 0, byTerNo = 0����Ϊ����ȫ���ն���Ϣ������Ϊ��ѯ�����ն���Ϣ
                                            */	
    
    h_ctrl_requestTerminalInfoResponce = 229,	    /********************<<  MT(��ϯ)�������ն���Ϣ��ƽ̨��Ӧ >>*******
                                            * Mcu-->ter
                                            * [��Ϣ��] u8(msg flag: 0 - get all, 1- get one)TTerminalInfo  �ն���Ϣ
                                            */
                                            

		h_ctrl_ModifyConfInfoReq = 230,               /********************<<  MT(��ϯ)�����޸����ٿ�������Ϣ >>***********
																									* ter-->Mcu
																									* [��Ϣ��] u8 ��ʾ�޸���(EModifyConfInfoType)
																									*          + �޸����ݳ���(u32)
																									*          + �޸����ݵ�buf
																									*/
		h_ctrl_ModifyConfInfoRsp = 231,               /********************<<  MT(��ϯ)�����޸����ٿ�������Ϣ�ظ� >>*******
																									* Mcu-->ter
																									* [��Ϣ��] u8 �޸���(EModifyConfInfoType)
																									*          + u8  �ɹ�/ʧ��(CtrlResult--h323adapter.h)
																									*/
    h_ctrl_requestTerminalInfoEx = 232,			/********************<<  MT(��ϯ)�������ն���Ϣ-�� >>*******
                                            * ter-->Mcu
                                            * [��Ϣ��] +u32(ʱ���)
                                            *          +TTERLABEL �ն�ID  ���� byMcuNo = 0, byTerNo = 0����Ϊ����ȫ���ն���Ϣ������Ϊ��ѯ�����ն���Ϣ
                                            */	
                                            
    h_ctrl_requestTerminalInfoResponceEx = 233,	/********************<<  MT(��ϯ)�������ն���Ϣ��ƽ̨��Ӧ-�� >>*******
                                            * Mcu-->ter
                                            * [��Ϣ��] +u32(ʱ���)
                                            *          +u8(msg end flag: 0 - not end, 1-end)
                                            *          +u8(msg flag: 0 - get all, 1- get one)
                                            *          +[u32(mtinfo buf size, ������) + [mt info buf]](�ն���Ϣ�б�)
                                            */
    h_ctrl_getDialogAuthReq = 234,                /********************<<  MT���� >>*******
                                            * ter-->Mcu
                                            * [��Ϣ��] ��
                                            */
    h_ctrl_getDialogAuthRsp = 235,                /********************<<  MCU��Ӧ >>*******
                                            * Mcu-->ter
                                            * [��Ϣ��] u8( 0 - ʧ�ܣ�1 - �ɹ� )
                                            */
    h_ctrl_giveupDialogAuthReq = 236,             /********************<<  MT���� >>*******
                                            * ter-->Mcu
                                            * [��Ϣ��] ��
                                            */
    h_ctrl_giveupDialogAuthRsp = 237,             /********************<<  MCU��Ӧ >>*******
                                            * Mcu-->ter
                                            * [��Ϣ��] u8( 0 - ʧ�ܣ�1 - �ɹ� )
                                            */
    h_ctrl_applySpeakerFailInd = 238,             /********************<<  MCU��Ӧ >>*******
                                            * Mcu-->ter
                                            * [��Ϣ��] ��
                                            */
		h_ctrl_confFailNtf = 239,                     /*****************���鷢������֪ͨ**********
																						*MCU--->ter
																						*[��Ϣ��]����ԭ��EConfFailureReason
																						*/
    h_ctrl_startDialogReq = 240,                  /*****************���뿪ʼ�Խ�ģʽ**********
                                            *ter-->Mcu, ��ϯר��
                                            *[��Ϣ��] ��
                                            */
    h_ctrl_startDialogRsp = 241,                  /*****************���뿪ʼ�Խ�ģʽ��Ӧ**********
                                            *MCU--->ter
                                            *[��Ϣ��] u8( 0 - ʧ�ܣ�1 - �ɹ� )
                                            */
    h_ctrl_stopDialogReq = 242,                   /*****************����ֹͣ�Խ�ģʽ**********
                                            *ter-->Mcu, ��ϯר��
                                            *[��Ϣ��] ��
                                            */
    h_ctrl_stopDialogRsp = 243,                  /*****************����ֹͣ�Խ�ģʽ��Ӧ**********
                                            *MCU--->ter
                                            *[��Ϣ��] u8( 0 - ʧ�ܣ�1 - �ɹ� )
                                            */
		h_ctrl_specDialogMtReq = 244,           /*****************��ϯָ���Խ��ն�**********
                                            *ter-->Mcu, ��ϯר��
                                            *[��Ϣ��] TTERLABEL
                                            */
    h_ctrl_specDialogMtRsp = 245,           /*****************��ϯָ���Խ��ն˻�Ӧ**********
                                            *MCU--->ter
                                            *[��Ϣ��] u8( 0 - ʧ�ܣ�1 - �ɹ� )
                                            */
		h_ctrl_confDialogStateNtf = 246,        /*****************����Խ�ģʽ״̬֪ͨ**********
                                            *MCU--->ter
                                            *[��Ϣ��] u8( ����Խ�ģʽ״̬��0 - �ǶԽ�ģʽ��1 - �Խ�ģʽ ) + [s8*N](����Խ�ģʽ�Ĵ����߱���������Խ�ģʽ״̬=1ʱ��Ч)
                                            */
		h_ctrl_youInDialogPosNtf = 247,			/*****************�ն˶Ի�λ��֪ͨ**********
                                            *MCU--->ter
                                            *[��Ϣ��] u8( 0 - ���ڶԽ�λ�ã�1 - �ڶԽ�λ�� )
                                            */
		h_ctrl_youInPresidePosNtf = 248,		/*****************�ն�����λ��֪ͨ**********
                                            *MCU--->ter
                                            *[��Ϣ��] u8( 0 - ��������λ�ã�1 - ������λ�� )
                                            */

		h_ctrl_termSwitchModeNtf = 249,			/*****************�ն��л�ģʽ֪ͨ**********
                                            *ter--->MCU
                                            *[��Ϣ��] u8 �л�ģʽ����( ETermSwitchMode )
                                            */	
	};
}

//�Ǳ���Ϣ�Ŷ���
typedef enum
{
	KDVP_NSM_START_ID						= 0,
	KDVP_NSM_GETMTLIST_REQ					= 1,			//MT ��GK���������ն��б�
	KDVP_NSM_GETMTLIST_RSP					= 2,			//����ƽ̨�ظ�KDVP_NSM_GETMTLIST_REQ

	KDVP_NSM_NEW_BEGIN						= (KDVP_NSM_START_ID + 10),
	KDVP_NSM_PALTFORMCAP_NOTIFY				= (KDVP_NSM_START_ID + 11),		//GK��֪h323ʵ��ƽ̨����
	KDVP_NSM_GETMTLIST_RSP2					= (KDVP_NSM_START_ID + 12),		//����ƽ̨�ظ�KDVP_NSM_GETMTLIST_REQ
	KDVP_NSM_GETMTLIST_REJECT				= (KDVP_NSM_START_ID + 13),		//4.2GK�ظ�KDVP_NSM_GETMTLIST_REQ
	
	//MT��GK�����ַ����Ϣ
	KDVP_NSM_ADDRBOOK_ENTRY_REQ				= (KDVP_NSM_START_ID + 14),
	KDVP_NSM_ADDRBOOK_ENTRY_REJECT			= (KDVP_NSM_START_ID + 15),
	KDVP_NSM_ADDRBOOK_ENTRY_RSP				= (KDVP_NSM_START_ID + 16),
	
	KDVP_NSM_ADDRBOOK_GROUP_REQ				= (KDVP_NSM_START_ID + 17),
	KDVP_NSM_ADDRBOOK_GROUP_REJECT			= (KDVP_NSM_START_ID + 18),
	KDVP_NSM_ADDRBOOK_GROUP_RSP				= (KDVP_NSM_START_ID + 19),
	
	KDVP_NSM_ADDRBOOK_GROUPLEVEL_REQ		= (KDVP_NSM_START_ID + 20),
	KDVP_NSM_ADDRBOOK_GROUPLEVEL_REJECT		= (KDVP_NSM_START_ID + 21),
	KDVP_NSM_ADDRBOOK_GROUPLEVEL_RSP		= (KDVP_NSM_START_ID + 22),
	
	//�ն�ע�� MT<-- >MTCarrier
	KDVP_NSM__REG_REQ						= (KDVP_NSM_START_ID + 23),										
	KDVP_NSM_REG_ACK						= (KDVP_NSM_START_ID + 24),
	KDVP_NSM_REG_NACK						= (KDVP_NSM_START_ID + 25),
	KDVP_NSM__ROUNDTRIP_TIMER				= (KDVP_NSM_START_ID + 26),
	
	//0.1 ����¼�� MT<-->GK
	KDVP_NSM_STARTP2PREC_REQ				= (KDVP_NSM_START_ID + 27),
	KDVP_NSM_STARTP2PREC_REJECT				= (KDVP_NSM_START_ID + 28),
	KDVP_NSM_STARTP2PREC_RSP				= (KDVP_NSM_START_ID + 29),
	
	//0.2 ��ֹ¼�� ˫���
	KDVP_NSM_STOPP2PREC_CMD					= (KDVP_NSM_START_ID + 30),
	KDVP_NSM_P2PRECSTATUS_NTY				= (KDVP_NSM_START_ID + 31),
	KDVP_NSM_P2PFASTUPDATE_CMD				= (KDVP_NSM_START_ID + 32),
	KDVP_NSM_P2P_COMMON_MSG					= (KDVP_NSM_START_ID + 33),

	KDVP_NSM_GETTSCATEGORY_REQ				= 100,		//MT ��TS��ѯ���ͣ���ҵ������Ӫ��
	KDVP_NSM_GETTSCATEGORY_RSP				= 101,		//�ظ�
	KDVP_NSM_DELETE_CALL					= 102,		//ɾ�����жԲ���
	KDVP_NSM_CREATECONF_REQ					= 103,		//MT->GK������������
	KDVP_NSM_CONFE164_NTF					= 104,   	//MT->GK��������ظ�����E164��
	KDVP_NSM_CREATECONF_RSP					= 105,  		//GK->MT��������ظ�
	KDVP_NSM_GETCONFLIST_REQ				= 106, 		//MT->��ȡ�����б�
	KDVP_NSM_GETCONFLIST_RSP				= 107,	 	//GK->MT�ظ������б�
	KDVP_NSM_JOINCONF_REQ					= 108,	 	//MT->GK�μӻ�������
	KDVP_NSM_JOINCONF_RSP					= 109,	 	//GK->MT�ظ��μӻ�������
	KDVP_NSM_CONFNUM_REQ					= 110,   	//MT->GK��ȡ������Ϳ��л����� 
	KDVP_NSM_CONFNUM_RSP					= 111,   	//GK->MT�ظ�������Ϳ��л�����
	KDVP_NSM_GETBOOKLIST_REQ				= 112,		//MT->GK��ȡԤԼ�����б�
	KDVP_NSM_GETBOOKLIST_RSP				= 113, 		//GK->MT����ԤԼ�����б�
	KDVP_NSM_CONFDETAIL_REQ					= 114,		//MT_GK��ȡ������ϸ��Ϣ(������д�������)
	KDVP_NSM_CONFDETAIL_RSP					= 115,    	//GK_MT�ظ�������ϸ��Ϣ
	KDVP_NSM_GETNEWCONFLIST_REQ				= 116, 		//MT->GK��ȡ��ʱ�����б�
	KDVP_NSM_GETNEWCONFLIST_RSP				= 117,	  
	KDVP_NSM_TEMPLATECONFLIST_REQ			= 118,		//MT_GK��ȡ����ģ���б�
	KDVP_NSM_TEMPLATECONFLIST_RSP			= 119,
	KDVP_NSM_NEWJOINCONF_REQ				= 120,    
	KDVP_NSM_NEWCREATECONF_REQ				= 121,  	

	KDVP_NSM_END_ID							= 200,
}emKDVPNsmType;

enum H245CtrlNonStandardMsgType 
{
	h_ctrl_nonstandardinvalid			= 101,
	h_ctrl_chairTransferReq				= 102,		//��ϯ�ն�ת����������	chair->MC, TTERLABEL
	h_ctrl_chairInviteTerminalReq		= 103,		//��ϯ�����ն�����		chair->MC, TTERADDR(vccommon.h)
	h_ctrl_terStatusReq					= 104,		//�ն�״̬����			MC->ter,   NULL
	h_ctrl_pollParamReq					= 105,		//��ѯ��ѯ����			MC->ter,   NULL	
	h_ctrl_whoViewThisTerReq			= 106,		//ѯ��MCU A�ն˱�˭ѡ��	ter->MC,   TTERLABEL(A)
	h_ctrl_confInfoReq					= 107,		//ѯ�ʻ�����Ϣ			ter->MC,   NULL
	h_ctrl_delayConfTimeReq				= 108,		//�ӳ�����ʱ��			chair->MC, u16, minutes
	h_ctrl_letTerViewMeReq				= 109,		//ǿ��ѡ������			ter->MC,   TTERLABEL(��ǿ��ѡ����) + 1BYTE(DataType) 
	h_ctrl_multicastTerReq				= 110,		//�鲥�ն�����			ter->MC,   TTERLABEL(Ŀ���ն�)	
	h_ctrl_destterStatusReq             = 111,		//Դ�ն�����Ŀ���ն�״̬     ter->MC,TTERLABEL(Ŀ���ն�)��

	h_ctrl_whoViewThisTerRsp			= 112,		//��ӦwhoViewThisTerReq	MC->ter, TTERLABEL(��ѡ���ն�) + 1Byte(ѡ���ն˸���) + TTERLABEL����
	h_ctrl_pollParamRsp					= 113,		//��ѯ����Ӧ��			ter->MC,  
													//����(1Byte,PollType) + ģʽ(1Byte,DataType) + ��ǰ״̬(1Byte, PollStatus)
													//+ ��ǰ��ѯ�����ն�(TTERLABEL��+ ʱ����(u16,s). ���û����ȫ��0)
													//�ն˸���(1Byte) + �б�(TTERLABEL���� + ʱ����(1Byte,s))

													//����(1Byte,PollType) + ģʽ(1Byte,DataType) + ʱ����(1Byte,s) + �ն˸���(1Byte) + �б�(TTERLABEL����)
	h_ctrl_confInfoRsp					= 114,		//�ش������Ϣ			MC->ter, ͸��ת����MTC
	h_ctrl_delayConfTimeRsp				= 115,		//�ӳ�����ʱ��Ӧ��		1BYTE,granted/denied
	h_ctrl_letTerViewMeRsp				= 116,		//ǿ��ѡ��Ӧ��			MC->ter,   1BYTE(granted/denied)
	
	h_ctrl_startVACReq					= 117,		//��ʼ������������ chair->MC, NULL
	h_ctrl_stopVACReq					= 118,		//ֹͣ������������ chair->MC, NULL
	h_ctrl_startVACRsp					= 119,		//��ʼ��������������Ӧ MC->ter, 1BYTE(granted/denied)
	h_ctrl_stopVACRsp					= 120,		//ֹͣ��������������Ӧ MC->ter,1BYTE(granted/denied)

	h_ctrl_startDiscussReq				= 121,		//��ʼ���� chair->MC, 1byte(ͬʱ�μ�����(����)�ĳ�Ա����)
	h_ctrl_stopDiscussReq				= 122,		//ֹͣ���� chair->MC, NULL
	h_ctrl_startDiscussRsp				= 123,		//��ʼ����������Ӧ MC->ter,1BYTE(granted/denied)
	h_ctrl_stopDiscussRsp				= 124,		//ֹͣ����������Ӧ MC->ter,1BYTE(granted/denied)
	
	h_ctrl_startVMPReq					= 125,		//��ʼ��Ƶ���� chair->MC, struct TVMPParam(vccommon.h)
	h_ctrl_stopVMPReq					= 126,		//ֹͣ��Ƶ���� chair->MC, NULL
	h_ctrl_changeVMPParamReq			= 127,		//�ı���Ƶ���ϲ��� chair->MC, struct TVMPParam
	h_ctrl_getVMPParamReq				= 128,		//�õ���Ƶ���ϲ��� chair->MC, NULL
	h_ctrl_startVMPRsp					= 129,		//��ʼ��Ƶ����������Ӧ MC->ter,1BYTE(granted/denied)
	h_ctrl_stopVMPRsp					= 130,		//ֹͣ��Ƶ����������Ӧ MC->ter,1BYTE(granted/denied)
	h_ctrl_changeVMPParamRsp			= 131,		//�ı���Ƶ���ϲ���������Ӧ MC->ter,1BYTE(granted/denied)
	h_ctrl_getVMPParamRsp				= 132,		//�õ���Ƶ���ϲ���������Ӧ MC->ter,struct TVMPParam
	
	h_ctrl_multicastTerRsp				= 133,		//�鲥�ն�Ӧ��   MC->ter,  TTERLABEL(Ŀ���ն�) + u32(ip,���ʧ��ipΪ0) 
													//                       + u16(��Ƶ�˿ں�)     + u16(��Ƶ�˿ں�)
													//                       + u8(��Ƶ��ʵ�غ�ֵ)  + u8(��Ƶ��ʵ�غ�ֵ)
													//                       + u8(��Ƶ��������)    + u8(��Ƶ��������) -- emEncryptTypeNone��
													//                       + TEncryptSync(��Ƶ������Ϣ) + TEncryptSync(��Ƶ������Ϣ)
	
	h_ctrl_destterStatusRsp             = 134,		//����Ŀ���ն�״̬����Ӧ   MC->ter,TTERLABEL(Ŀ���ն�) + _TTERSTATUS(vccommon.h)

	h_ctrl_makeTerQuietCmd				= 135,		//Զ�˾�������			ter->MC,MC->ter,  TTERLABEL(dst) + 1BYTE(turn_on/turn_off)
	h_ctrl_makeTerMuteCmd				= 136,		//Զ����������			ter->MC,MC->ter,  TTERLABEL(dst) + 1BYTE(turn_on/turn_off)
	h_ctrl_startPollCmd					= 137,		//��ʼ��ѯ����			MC->ter,    
													//����(1Byte,PollType) + ģʽ(1Byte,DataType) + �ն˸���(1Byte) + �б�(TTERLABEL���� + ʱ����(1Byte,s))
	h_ctrl_stopPollCmd		   			= 138,		//ֹͣ��ѯ����			MC->ter,	NULL
	h_ctrl_pausePollCmd					= 139,		//��ͣ��ѯ				MC->ter,	NULL
	h_ctrl_resumePollCmd				= 140,		//�ָ���ѯ				MC->ter,	NULL
													//						action(1Byte,������ͨ����:turn_on(��ʼ)/turn_off(ֹͣ);����Ԥ������:�����1-4��ʾԤ��λ)
	h_ctrl_stopViewMeCmd				= 141,		//ֹͣǿ��ѡ��			ter->MC
	h_ctrl_stopMulticastTer				= 142,		//ֹͣ�鲥�ն�			ter->MC,	TTERLABEL
	
    h_ctrl_chairSelectViewCmd			= 144,		//��ϯѡ��				ter->MC,    <m,t> + 1Byte(type_audio/type_video/type_av)	

	h_ctrl_chairInviteFailedInd			= 145,		//��ϯ�����ն�ʧ��		MC->chair, TTERADDR
	h_ctrl_confWillEndInd				= 146,		//���鼴������ָʾ		MC->chair, u16 minutes, ��ʾ���ж�ý���
	h_ctrl_delayConfTimeInd             = 147,		//�ӳ�����ʱ��ָʾ      MC->ter, u16 ����
	h_ctrl_terApplyChairInd				= 148,		//���ն���Ind,					//�ն�״ָ̬ʾ			ter->MC,   _TTERSTATUS ( response h_ctrl_terStatusReq)	
	h_ctrl_terStatusInd					= 149,		//�ն�״ָ̬ʾ			ter->MC,   _TTERSTATUS ( response h_ctrl_terStatusReq)	
	h_ctrl_pollParamInd                 = 150,		//��ѯ״ָ̬ʾ          ����(1Byte,PollType) + ģʽ(1Byte,DataType) + ��ǰ״̬(1Byte, PollStatus) 
													// + ��ǰ��ѯ�����ն�(TTERLABEL��+ ʱ����(u16,s). ���û����ȫ��0)
	h_ctrl_smsInd						= 151,		//����Ϣָʾ			ter->MC,MC->ter,TTERLABEL(src) + TTERLABEL(dst) + (1BYTE:��������)+�ַ���('\0'����)	
	h_ctrl_broadcasterTokenOwnerInd		= 152,		//�¹㲥Դͨ��			MC->ter, TTERLABEL
	
    h_ctrl_termSourceNameInd            = 157,		//�ն���ƵԴ����ָʾ    MC->ter,��Ϣ�����ַ�����'\0'����
	
    h_ctrl_termVideoSrcCmd				= 162,		//ѡ���ն���ƵԴ		MC->ter, 1BYTE(��ƵԴ����0:S���� 1~16:C����)

	h_ctrl_chimeInReq					= 163,		//�ն�����廰				ter->MC,		NULL
	h_ctrl_makeTerChimeInCmd			= 164,		//��ϯָ���ն˲廰			ter->MC,		TTERLABEL
	h_ctrl_chimeInInd					= 165,		//�ն˲廰״̬				MC->ter			1�ֽڣ�0: ���ڲ廰, 1: �ڲ廰��
	h_ctrl_otherTerChimeInInd			= 166,		//�����ն�����廰ָʾ		MC->chair		TTERLABEL

    //add by jason 2005-10-11
    h_ctrl_SimpleConfInfoInd            = 189,		//mcu֪ͨ�ն˸��»�����Ϣ      MC->ter			1�ֽڣ�0: ���ڲ廰, 1: �ڲ廰��
    
    h_ctrl_terBandWidthInd              = 190,		//mt���շ��ʹ���֪ͨ           ter->MC      u16(���մ���������Ƶ����Ƶ��,������) + u16(���ʹ���������Ƶ����Ƶ��,������)
    h_ctrl_terBitrateInfoReq            = 191,		//mcu�����ն�����              MC->ter      ��Ϣ�壺��
    h_ctrl_terBitrateInfoRsp            = 192,		//mt���ն�����Ӧ��             ter->MC      ��Ϣ�壺_TERBITRATE
	
    h_ctrl_ViewBroadcastingSrcCmd       = 217,		/*��ϯ�ն�ǿ�ƹ㲥, ��Ϣ��: u8 (opr_start-��ʼ��opr_stop��ȡ��)*/
    
    h_ctrl_SatDConfAddrInd              = 218,		/*******************<< ���Ƿ�ɢ������յ�ַ֪ͨ >>*************
														* Mcu-->ter
														*[��Ϣ��](��������)
														*    +   u32   ��һ·��Ƶ��ַ
														*    +   u16   ��һ·��Ƶ�˿�
														*    +   u32   ��һ·��Ƶ��ַ
														*    +   u16   ��һ·��Ƶ�˿�
														*    +   u32   �ڶ�·��Ƶ��ַ
														*    +   u16   �ڶ�·��Ƶ�˿�
														*/

	 h_ctrl_videoFormatChangeCmd			,		/*********************<< ��Ƶ�ֱ��ʵ���  >>********************
														* Mcu-->ter
														*[��Ϣ��]
														*
														*    +   u8  ͨ������   LOGCHL_VIDEO      (Ĭ������Ƶͨ��)
														*    +   u8  �ֱ������� VIDEO_FORMAT_CIF, VIDEO_FORMAT_QCIF, VIDEO_FORMAT_SQCIF_* ��
														*/
														
    

    h_ctrl_setAudioVolumeCmd				,		/*********************<<  �ն���������   >>********************
														* Mcu-->ter
														*[��Ϣ��]
														*
														*    +   u8  ��������(NOTE: VOLUME_TYPE_OUT or VOLUME_TYPE_IN)
														*    +   u8  �����������(NOTE: vx linux 0��32; PCMT: 0��255)
														*/
    
    h_ctrl_someOfferingNtf					,		/********************<<  �ն�֪ͨͨ����Ϣ >>*******************
														* Mcu-->ter
														*[��Ϣ��]
														*
														*    Mcu2MtNtfMsgType
														*/ 
                                             
    h_ctrl_videoFrameRateChangeCmd			,		/********************<<  (��һ·)��Ƶ����֡�ʵ��� >>***********
														* Mc-->ter
														*[��Ϣ��]
														*
														*    +   u8  ����֡��
														*/

	h_ctrl_removeMixMemberCmd				,		/********************<<  �Ƴ����ƻ����е��ն� (����ϯ������Ч) >>*******************
														* Mt-->Mc
														*[��Ϣ��]
														*
														*    +   TMt ����
														* 
														*/
	h_ctrl_discussParamInd					,		/*******************<< ������Ϣ֪ͨ>>***************************
														* Mt-->Mc
														* [��Ϣ��]
														* + TDiscussParam
														*
														*/
	h_ctrl_videoFormatRecoverCmd			,		/******************<<  �ն˷ֱ��ʻָ�����   >>****not in use now**********
														* ter-->Mt
														* [��Ϣ��]  ��
														*/
	h_ctrl_mtSelectVmpReq					,		/*******************<< �նˣ�������ϯMT��ѡ������ϳ����� >>**************
														* ter --> MC
														* [��Ϣ��] u8	1��start,0��stop
														*/
	h_ctrl_mtSelectVmpRsp					,		/*******************<< �նˣ�������ϯMT��ѡ������ϳ�Ӧ�� >>**************
														* MC --> ter
														* [��Ϣ��] u8  ok/fail(1��ok��0��fail)
														*/	
    h_ctrl_mtSpeakStatusNtf					,		/*******************<< �ն� ���뷢���е��ն�              >>**************
														* MC --> ter
														* [��Ϣ��] emMtSpeakerStatus
														*
                                                             emWaiting       = 1,        //�ȴ�ͬ�⣻mcu���ᷢ�ʹ�״̬���ն��ڷ������� �� ��Ϊ������֪ͨ �� ֮ǰ���Զ������״̬
                                                             emAgreed        = 2,        //�����ˣ�
                                                             emDenid         = 3,        //���뱻�ܾ���
                                                             enCanceled      = 4,        //��ȡ�����ԣ�
														*/	

    h_ctrl_confSpeakModeNtf					,		/*******************<< �ն� ��������ն�                 >>**************
														* MC --> ter
														* [��Ϣ��] emConfSpeakMode
                                                            emNormal            = 0,        //��ͨ����ģʽ����ϯָ��/���ָ��/һ����ն�����
                                                            emAnswerInstantly   = 1         //����ģʽ
														*/	

    h_ctrl_applycancelspeakerReq			,		/*******************<< �������ն� ��> MCU                 >>**************
														* ter --> MC
														* [��Ϣ��] u8:0-ȡ������ 1-���뷢��
														*/	

    h_ctrl_applycancelspeakerRsp			,		/*******************<< MCU ��>  �������ն�                >>**************
														* MC --> ter
														* [��Ϣ��] u8:0-ȡ������ 1-���뷢��
															u8 result: granted/denied
														*/	

	h_ctrl_videoFpsChangeCmd				,		/*********************<< ��Ƶ֡�ʵ���  >>********************
														* Mcu-->ter
														*[��Ϣ��]
										 				*
										 				*    +   u8  ͨ������   LOGCHL_VIDEO      (Ĭ������Ƶͨ��)
														*    +   u8  ֡��ֵ 
														*/

	h_ctrl_videoAliasCmd					,		/*********************<< mcu��ȡ�ն���ƵԴ����  >>********************
														* Mcu-->ter
														*[��Ϣ��] ��
														*
														*    
														*    
														*/
	h_ctrl_videoAliasInd					,		/*********************<< �ն���ƵԴ����ָʾ  >>********************
														* ter-->Mcu
														*[��Ϣ��]
														*  u8 byVidNum����ƵԴ������+ u8 byVidIdx����ƵԴ�˿�������+   
														*  u8 byAliaseLen���������ȣ�+ s8 *pchAlias��������+ 
														*  u8 byVidIdx����ƵԴ�˿�������+ u8 byAliaseLen���������ȣ�+  
														*  s8 *pchAlias��������+ ...
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
	h_ctrl_transparentMsgNtf = 236,    /***************<< ���桢�ն�͸����Ϣ  >>********************
										* ter<-->Mcu
										*[��Ϣ��]
										*     ������Ϣ���Ͳ�ͬ����Ϣ�����ݲ�ͬ
										*      
										*/  
										
	h_ctrl_CodingFormNtf = 237,         /**************<< ��h245������������Զ˷��͸÷Ǳ���Ϣͨ��Զ˱��˵ı��뷽ʽ  >>********************
										 * ter<-->Mcu
										 *[��Ϣ��]
									     * u8(���뷽ʽ)
										 *      
										 */
	h_ctrl_nonstandardVrsDef = 238,     /***************<<�Ǳ��Զ��塷******************
                                         * ter<-->Mcu
                                         *[��Ϣ��]
                                         *     ������Ϣ���Ͳ�ͬ����Ϣ�����ݲ�ͬ
                                         *     �ϲ�����ҵ��Э����Ϣ�������ͺ���Ϣ����
                                         *
							             */
//[20140704]
	h_ctrl_StartMtVmpReq = 239,		/********** <<�ն˿�������ϳ�����>>*************************
   									 * ter -->Mcu
   									 * [��Ϣ��]
									 * u8(����ϳ����ͣ�vccommon.h�ж���) ) 
									 * u8(����ϳɷ�ʽ��vccommon.h�ж���) ) 
  	 								 * u8(����ϳɷ��vccommon.h�ж���) 
   									 * u8(byLen-��Ч��Ա��)
   									 * ��u8(ͨ����)  + TVMPMember��* byLen
									 */

	h_ctrl_StartMtVmpRsp = 240,		/***********<<ֹͣ�ն˻���ϳ�����>>**************************          
									 * ter --> Mcu  
									 * [��Ϣ��]
									 * u8(����ϳ����ͣ�vccommon.h�ж���)
									 */

	h_ctrl_StartMtVmpNotify = 241,	/************<<�ն˿�������ϳ�ͨ��>>***************************
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


	h_ctrl_StopMtVmpReq = 242, 		/************<<ֹͣ�ն˻���ϳ�����>>***************************          
									 * ter --> Mcu  
									 * [��Ϣ��]
									 * u8(����ϳ����ͣ�vccommon.h�ж���)
									 */

	h_ctrl_StopMtVmpRsp = 243,		/************<<ֹͣ�ն˻���ϳ�����Ӧ��>>***************************          
									 * Mcu --> ter 
									 * [��Ϣ��]
									 * u8(0-�ɹ� 1-ʧ��)
									 * u8(����ϳ����ͣ�vccommon.h�ж���) */

	h_ctrl_StopMtVmpNotify = 244,   /************<<ֹͣ�ն˻���ϳ�����Ӧ��>>***************************          
									 * Mcu --> ter 
									 * [��Ϣ��]
									 * u8(0-�ɹ� 1-ʧ��)
									 * u8(����ϳ����ͣ�vccommon.h�ж���) 
									 */


	h_ctrl_ChangeMtVmpReq = 245,	/************<<�����ն˻���ϳ�����>>***************************
 									 * ter -->Mcu
 									 * [��Ϣ��]
									 * u8(����ϳ����ͣ�vccommon.h�ж���)
									 * u8(����ϳɷ�ʽ��vccommon.h�ж���)
 									 * u8(����ϳɷ��vccommon.h�ж���) 
 									 * u8(byLen-��Ч��Ա��)
 									 * ��u8(ͨ����)  + TVMPMember��* byLen
									 */

	h_ctrl_ChangeMtVmpRsp = 246, 	/************<<�����ն���������ϳ�����Ӧ��>>***************************
 									 * Mcu -->ter
 									 * [��Ϣ��]
									 * u8(0-�ɹ� 1-ʧ��)
									 * u8(����ϳ����ͣ�vccommon.h�ж���)
									 */

	h_ctrl_ChangeMtVmpNotify = 247,	/************<<�����ն˻���ϳ�ͨ��>>***************************
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
	h_ctrl_chimeInFailInd = 260,			/********************<<  MT����廰ʧ�� >>*******************
											* Mc-->ter
											*[��Ϣ��] ��
											*
											*/

	h_ctrl_ModifyConfNameReq = 261,			/********************<<  MT�����޸Ļ������� >>*******************
											* ter-->Mcu
											* [��Ϣ��] s8[64+1]  ��������
											*
											*/

	h_ctrl_ModifyConfNameRsp = 262,			/********************<<  MT�����޸Ļ������� >>*******************
											* Mcu-->ter
											* [��Ϣ��] u8  �ɹ�/ʧ��
											*
											*/

	h_ctrl_ModifyConfDurationCmd = 263,		/********************<<  MT�����޸Ļ���ʱ�� >>*******************
											* ter-->Mcu
											* [��Ϣ��] u16	ʱ������λ�Ƿ���
											*
											*/

	h_ctrl_ModifyConfPwdCmd = 264,			/********************<<  MT�����޸Ļ���������� >>*******************
											* ter-->Mcu
											* [��Ϣ��] u8	�Ƿ���� 
											*          + s8[16+1] �������
											*
	                                        */

	h_ctrl_requestTerminalInfo = 265,		/********************<<  MT(��ϯ)�������ն���Ϣ >>*******
                                            * ter-->Mcu
                                            * [��Ϣ��] TTERLABEL �ն�ID  -- byMcuNo = 0, byTerNo = 0����Ϊ����ȫ���ն���Ϣ������Ϊ��ѯ�����ն���Ϣ
                                            */

	h_ctrl_requestTerminalInfoResponce = 266,	/********************<<  MT(��ϯ)�������ն���Ϣ��ƽ̨��Ӧ >>*******
												* Mcu-->ter
												* [��Ϣ��] u8(msg flag: 0 - get all, 1- get one)TTerminalInfo  �ն���Ϣ(adapter42.h,����ȡ)
												*/

	h_ctrl_ModifyConfInfoReq = 267,         /********************<<  MT(��ϯ)�����޸����ٿ�������Ϣ >>***********
											* ter-->Mcu
											* [��Ϣ��] u8 ��ʾ�޸���(EModifyConfInfoType) (vccommon.h)
											*          + �޸����ݳ���(u32)
											*          + �޸����ݵ�buf
											*/
	h_ctrl_ModifyConfInfoRsp = 268,         /********************<<  MT(��ϯ)�����޸����ٿ�������Ϣ�ظ� >>*******
											* Mcu-->ter
											* [��Ϣ��] u8 �޸���(EModifyConfInfoType)
											*          + u8  �ɹ�/ʧ��(CtrlResult--h323adapter.h)
											*/
	h_ctrl_requestTerminalInfoEx = 269,		/********************<<  MT(��ϯ)�������ն���Ϣ-�� >>*******
                                            * ter-->Mcu
                                            * [��Ϣ��] +u32(ʱ���)
                                            *          +TTERLABEL �ն�ID  -- byMcuNo = 0, byTerNo = 0����Ϊ����ȫ���ն���Ϣ������Ϊ��ѯ�����ն���Ϣ
                                            */	
                                            
    h_ctrl_requestTerminalInfoResponceEx = 270,		/********************<<  MT(��ϯ)�������ն���Ϣ��ƽ̨��Ӧ-�� >>*******
													* Mcu-->ter
													* [��Ϣ��] +u32(ʱ���)
													*          +u8(msg end flag: 0 - not end, 1-end)
													*          +u8(msg flag: 0 - get all, 1- get one)
													*          +[u32(mtinfo buf size, ������) + [mt info buf]](�ն���Ϣ�б�)
													*/

	h_ctrl_getDialogAuthReq = 271,          /********************<<  MT���� >>*******
                                            * ter-->Mcu
                                            * [��Ϣ��] ��
                                            */

	h_ctrl_getDialogAuthRsp = 272,          /********************<<  MCU��Ӧ >>*******
                                            * Mcu-->ter
                                            * [��Ϣ��] u8( 0 - ʧ�ܣ�1 - �ɹ� )
                                            */

	h_ctrl_giveupDialogAuthReq = 273,       /********************<<  MT���� >>*******
                                            * ter-->Mcu
                                            * [��Ϣ��] ��
                                            */

	h_ctrl_giveupDialogAuthRsp = 274,       /********************<<  MCU��Ӧ >>*******
                                            * Mcu-->ter
                                            * [��Ϣ��] u8( 0 - ʧ�ܣ�1 - �ɹ� )
                                            */

	h_ctrl_applySpeakerFailInd = 275,       /********************<<  MCU��Ӧ >>*******
                                            * Mcu-->ter
                                            * [��Ϣ��] ��
                                            */

	h_ctrl_confFailNtf = 276,               /*****************���鷢������֪ͨ**********
											*MCU--->ter
											*[��Ϣ��]����ԭ��EConfFailureReason
											*/

	h_ctrl_startDialogReq = 277,            /*****************���뿪ʼ�Խ�ģʽ**********
                                            *ter-->Mcu, ��ϯר��
                                            *[��Ϣ��] ��
                                            */

	h_ctrl_startDialogRsp = 278,            /*****************���뿪ʼ�Խ�ģʽ��Ӧ**********
                                            *MCU--->ter
                                            *[��Ϣ��] u8( 0 - ʧ�ܣ�1 - �ɹ� )
                                            */

	h_ctrl_stopDialogReq = 279,             /*****************����ֹͣ�Խ�ģʽ**********
                                            *ter-->Mcu, ��ϯר��
                                            *[��Ϣ��] ��
                                            */

	h_ctrl_stopDialogRsp = 280,             /*****************����ֹͣ�Խ�ģʽ��Ӧ**********
                                            *MCU--->ter
                                            *[��Ϣ��] u8( 0 - ʧ�ܣ�1 - �ɹ� )
                                            */

	h_ctrl_specDialogMtReq = 281,			/*****************��ϯָ���Խ��ն�**********
                                            *ter-->Mcu, ��ϯר��
                                            *[��Ϣ��] TTERLABEL
                                            */

	h_ctrl_specDialogMtRsp = 282,			/*****************��ϯָ���Խ��ն˻�Ӧ**********
                                            *MCU--->ter
                                            *[��Ϣ��] u8( 0 - ʧ�ܣ�1 - �ɹ� )
                                            */

	h_ctrl_confDialogStateNtf = 283,		/*****************����Խ�ģʽ״̬֪ͨ**********
                                            *MCU--->ter
                                            *[��Ϣ��] u8( ����Խ�ģʽ״̬��0 - �ǶԽ�ģʽ��1 - �Խ�ģʽ ) + [s8*N](����Խ�ģʽ�Ĵ����߱���������Խ�ģʽ״̬=1ʱ��Ч)
                                            */

	h_ctrl_youInDialogPosNtf = 284,			/*****************�ն˶Ի�λ��֪ͨ**********
                                            *MCU--->ter
                                            *[��Ϣ��] u8( 0 - ���ڶԽ�λ�ã�1 - �ڶԽ�λ�� )
                                            */
//285
	h_ctrl_youInPresidePosNtf				= 285,		/*****************�ն�����λ��֪ͨ**********
													    *MCU--->ter
														*[��Ϣ��] u8( 0 - ��������λ�ã�1 - ������λ�� )
														*/

	//////////////////////////////////////////////////////////////////////////
	h_ctrl_nonstandstart					= 300,	//

	h_ctrl_quietRequest						= 301,  //Զ�˾�������,				[outgoing]: [TTERLABEL]
	h_ctrl_quietResponse					= 302,  //Զ�˾�����Ӧ				[incoming]: [TTERLABEL+u8:CtrlResult]

	h_ctrl_cancelQuietRequest				= 303,  //ȡ��Զ�˾�������			[outgoing]: [TTERLABEL]
	h_ctrl_cancelQuietResponse				= 304,  //ȡ��Զ�˾�����Ӧ			[incoming]: [TTERLABEL+u8:CtrlResult]

	h_ctrl_muteRequest						= 305,  //Զ�˱�������,				[outgoing]: [TTERLABEL]
	h_ctrl_muteResponse 					= 306,  //Զ�˱�����Ӧ				[incoming]: [TTERLABEL+u8:CtrlResult]

	h_ctrl_cancelMuteRequest				= 307,  //ȡ��Զ�˱�������			[outgoing]: [TTERLABEL]
	h_ctrl_cancelMuteResponse				= 308,  //ȡ��Զ�˱�����Ӧ			[incoming]: [TTERLABEL+u8:CtrlResult]

	h_ctrl_setVACReqequest					= 309,  //���������л�(��������)	[outgoing]: [u8+DW] 0�����������л�1��ȡ�������л�+1 DW ��������(0~100֮���һ��ֵ),����û���������ޣ���ʱʹ��ȱʡ����������
	h_ctrl_setVACResponse					= 310,  //���������л����			[incoming]: [u8:CtrlResult](�����Ƕ����ò����Ľ�������Ǳ�����ǰ�����л���״̬�����磬ȡ�������л��Ľ��Ϊ�ɹ�����ʾȡ�������л������óɹ���)

	h_ctrl_startDiscussRequest				= 311,  //��ʼ��������				[outgoing]: NULL
	h_ctrl_startDiscussResponse				= 312,  //�������۽��				[incoming]: [u8:CtrlResult]�ն��յ��������,���л᳡����,ȫ��ȡ������
	
	h_ctrl_setMultiPicRequest				= 313,  //���ö໭��				[outgoing]: TMultiPic
	h_ctrl_setMultiPicResponse				= 314,  //
	h_ctrl_notInConfTerminalListRequest		= 315,	//��������δ���᳡��	[outgoing]: NULL
	h_ctrl_notInConfTerminalListResponse	= 316,	//����δ���᳡��Ӧ��	[incoming]: [TTERINFO[]]

	h_ctrl_callTerminal						= 317,  //�������߻᳡				[outgoing]: [TTERLABEL]
	h_ctrl_disconnectTerminal				= 318,  //�Ҷ��ն�					[outgoing]: [TTERLABEL]
	h_ctrl_selectSpeakingUserRequest		= 319,	//��������					[outgoing]: [TTERLABEL]
	h_ctrl_selectSpeakingUserResponse		= 320,  //�������Խ��				[incoming]: [TTERLABEL+u8:CtrlResult]
	h_ctrl_setPicSwitch						= 321,	//��,�໭���л�				[outgoing]: [u8] 0:������;1:�໭��
    h_ctrl_capabilitiesInd					= 322,  //��ͨ����ָʾ              [incoming]: [TCAPINFO]
    h_ctrl_serialPortData					= 323,  //��������                  [incoming]&[outgoing]: [TCOMDATA]

	h_ctrl_setChanMultiCastAddr				= 400,  //����ͨ���鲥��ַ			[incoming]&[outgoing]: [TCHANMULTICAST]
	h_ctrl_serialNumber      				= 401,  //���к�    				[incoming]&[outgoing]: [u8[]] 
    h_ctrl_startDataConfRequest				= 402,  //����ʼ���ݻ���          NULL
	h_ctrl_startDataConfResponse			= 403,  //Ӧ��ʼ���ݻ���          [incoming]&[outgoing]: u8: result

	h_ctrl_askVcsOccupyPermit				= 500,	//
	h_ctrl_askVcsOccupyPermitResp			= 501,  //
	h_ctrl_requestConfTerminalIDs			= 502,  // ��������ն�E164��      [outgoing]
	h_ctrl_requestConfTerminalIDsResponse	= 503,	// Ӧ��
	h_ctrl_requestTerminalE164				= 504,	//terѯ���ն�E164	    ter->MC,   [incoming]&[outgoing]: []
	h_ctrl_requestTerminalE164Responce		= 505,	//MC�ش��ն���E164	    MC->ter,   [incoming]&[outgoing]: []

	h_ctrl_VersionIdInd						= 600,	// ��Ϣ��Ϊu8[LEN_256]
	h_ctrl_KdvpExtraConfNSNInfo				= 601,	// ����192���ն��б�������Ǳ� [incoming]&[outgoing]

	h_ctrl_startVMPNotify					= 602,	//��h_ctrl_startVMPReq, h_ctrl_startVMPRsp���Ӧ
	h_ctrl_stopVMPNotify					= 603,	//��h_ctrl_stopVMPReq, h_ctrl_stopVMPRsp���Ӧ
	h_ctrl_changeVMPParamNotify				= 604,	//��h_ctrl_changeVMPParamReq, h_ctrl_changeVMPParamRsp���Ӧ
	
	h_ctrl_SecVidSrcInd						= 605,		//sip�� ֪ͨ˫��Դ��˭
	
#ifdef _ENABLE_QUANTUM_PROJECT_
	h_ctrl_QuantumMideaKey           =701, //ƽ̨֪ͨ�ڻ�������ն�MideaKey��Э��ֻ����͸��
#endif
	// �绰�ն�����
    h_ctrl_joinConferenceNtf				= 1001,        /********************<< Mcu to Phone>>**************************/
    h_ctrl_TerminalJoinNtf					= 1002,
    h_ctrl_TerminalLeftNtf					= 1003,
    h_ctrl_youQuietNtf						= 1004,
    h_ctrl_youMuteNtf						= 1005,
    h_ctrl_youAreSpeaker					= 1006,
    h_ctrl_youAreJoinAudMixer				= 1007,
    h_ctrl_terminalApplyAsSpeakerRsp		= 1008,
    h_ctrl_terminalChimeInRsp				= 1009,
    h_ctrl_joinedTerminalNumNtf				= 1010,

    h_ctrl_phoneStatusReq					= 1050,
    h_ctrl_joinedTerminalNumReq				= 1051,
    h_ctrl_confInfoNtf						= 1052,
	
	//����vip�б���Ϣ����
	h_ctrl_VipListReq						= 1101,
	h_ctrl_VipListRsp						= 1102,
	h_ctrl_VipListNotify					= 1103,

	h_ctrl_dataConfCreatedNtf				= 1104,		//�װ���鴴��֪ͨ mt -> mcu, �ַ�����confname
	h_ctrl_joinDataConfCmd					= 1105,		//����װ�������� mcu -> mt, �ַ�����confname

	h_ctrl_allLocAliasNotif					= 1106,     //�ն�֪ͨ����ͨ������
	h_ctrl_selectViewChnCmd					= 1107,		//ָ��ѡ��ĳ�ն�ĳͨ��

	//���ter-->mc��Ӧ�ķǱ�����ID��
	h_ctrl_chairSpecifyDualStream			= 1108,		//Chair --> MC ָ������ն˷�˫�� 
	h_ctrl_bitRatePercentage				= 1109,		//MT --> MC    ָ����ǰ�ն˶�·����ͨ�����ʵı���

    h_ctrl_cancelSelectViewChnCmd			= 1110,		//ȡ��ָ��ѡ��ĳ�ն�ĳͨ��

	h_ctrl_nonstandard_fecc					= 1111,		
	
	h_ctrl_terGetTerVidAliasReq             = 1112,  //�ն���ƽ̨��ȡ�����ն˵���ƵԴ����

	h_ctrl_terGetTerVidAliasRsp             = 1113,  //ƽ̨�ظ��ն� �����ն˵���ƵԴ����
	
	h_ctrl_getTerCameraPosCmd               = 1114, // ƽ̨��ȡ�ն�Ԥ��λ��Ϣ
	h_ctrl_terCameraPosNtf				    = 1115, // �ն�Ԥ��λ��Ϣ�ϱ�

	h_ctrl_terGetTerCameraPosCmd            = 1116, // �ն���ƽ̨��ȡ�����ն�Ԥ��λ��Ϣ
	h_ctrl_terGetTerCameraPosNtf            = 1117, // ƽ̨�ظ��ն������ն�Ԥ��λ��Ϣ

	h_ctrl_GetTerLossRateCmd		= 1118,	 //mcu��ȡ�ն˶�����
	h_ctrl_terGetTerLossRateNtf		= 1119,	 //mt��mcu���Ͷ�����֪ͨ
	h_ctrl_bFeccSupport             = 1120,  //�Ƿ�֧��fec ���ܣ� mt->mcu, mcu->mt
	h_ctrl_KedaManuProduct          = 1121, //������������ʶ�� mt<-->mcu���Ǳ����ݣ�
																					//V5.0 <--> V5.0: protobuf
																					//V5.0 <--> V4.x(HD3): TKedaManuProduct
																					//TPS <--> TPS: TKedaManuProduct

	h_ctrl_nonstandard_general				= 2000,		//Jacky Wei: a general nonstandard event id for KDV v5.0
	h_ctrl_nonstandardend					= 2001,
};

//��ҵ�Ǳ�h_ctrl_nonstandardinvalid����Ϊ101����h_ctrl_mcuvccommonnonstandstart��ͻ
#define h_ctrl_nonstandardinvalid	h_ctrl_mcuvccommonnonstandstart



/////////////////////////  ��kdv323adapter.h������ļ���������Ϣ�ͽṹ�� begin  /////////
enum H323MCUMsgType
{
		CASCADE_MSGTYPE_BEGINNING		= 0,
        
        H_CASCADE_REGUNREG_REQ			= 1,   //[IN]&[OUT]:[TRegUnRegReq]	register request
        H_CASCADE_REGUNREG_RSP			= 2,   //[IN]&[OUT]:[TRegUnRegRsp]	register response
        
        H_CASCADE_NEWROSTER_NTF			= 3,   //[IN]&[OUT]:[TRosterList]  roster notify
        
        H_CASCADE_PARTLIST_REQ			= 4,   //[IN]&[OUT]:[TReq]         request part list 
        H_CASCADE_PARTLIST_RSP			= 5,   //[IN]&[OUT]:[TPartListRsp] reponse part list (dwpid ==0 ��ʾ�Է���MCU)
        
        H_CASCADE_INVITEPART_REQ		= 6,	//[IN]&[OUT]:[TInvitePartReq]  invite part request
        H_CASCADE_INVITEPART_RSP		= 7,	//[IN]&[OUT]:[Tsp]             invite part response
        H_CASCADE_NEWPART_NTF			= 8,    //[IN]&[OUT]:[TPart]           new part notify
        
        H_CASCADE_CALL_ALERTING_NTF		= 9,	//[IN]&[OUT]:[TCallNtf]
        
        H_CASCADE_REINVITEPART_REQ		= 10,	 //[IN]&[OUT]:[TReInviteReq]    reinvite part request
        H_CASCADE_REINVITEPART_RSP		= 11,	//[IN]&[OUT]:[Tsp]        reinvite part response
        
        H_CASCADE_DISCONNPART_REQ		= 12,	//[IN]&[OUT]:[TPartReq]     disconnect part request
        H_CASCADE_DISCONNPART_RSP		= 13,	//[IN]&[OUT]:[Tsp]         disconnect part response
        H_CASCADE_DISCONNPART_NTF		= 14,	//[IN]&[OUT]:[TDiscPartNF] disconnect part notify
        
        
        H_CASCADE_DELETEPART_REQ		= 15,	//[IN]&[OUT]:[TPartReq]		delete part request
        H_CASCADE_DELETEPART_RSP		= 16,	//[IN]&[OUT]:[Tsp]			delete part response
        H_CASCADE_DELETEPART_NTF		= 17,	//[IN]&[OUT]:[TPartNtf]   delete part notify (whether or not local)
        
        H_CASCADE_SETIN_REQ				= 18,      //[IN]&[OUT]:[TSetInReq]    request video in
        H_CASCADE_SETIN_RSP				= 19,      //[IN]&[OUT]:[Tsp]          response msg
        
        H_CASCADE_SETOUT_REQ			= 20,     //[IN]&[OUT]:[TSetOutReq]//��Ƶ������Լ�������(��Ƶ����:MCU->MT)
        H_CASCADE_SETOUT_RSP			= 21,     //[IN]&[OUT]:[Tsp]//��Ƶ������Լ���Ӧ��(��Ƶ����:MCU->MT)
        
        H_CASCADE_OUTPUT_NTF			= 22,     //[IN]&[OUT]:[TPartOutputNtf]      video output notify (dwpid ==0 ��ʾ�Է���MCU)
        
        H_CASCADE_NEWSPEAKER_NTF		= 23,	//[IN]&[OUT]:[TNewSpeakerNtf]      newSpeaker output notify (dwpid ==0 ��ʾ�Է���MCU)
        
        H_CASCADE_AUDIOINFO_REQ			= 24,	//[IN]&[OUT]:[TConfVideInfoReq]         audio info request 
        H_CASCADE_AUDIOINFO_RSP			= 25,   //[IN]&[OUT]:[TConfAudioInfo]    audio info response
        
        H_CASCADE_VIDEOINFO_REQ			= 26,	//[IN]&[OUT]:[pReq]          conference videoinfo request 
        H_CASCADE_VIDEOINFO_RSP			= 27,	//[IN]&[OUT]:[TConfVideoInfo] conference videoinfo response
        
        
        H_CASCADE_CONFVIEW_CHG_NTF		= 28,	//[IN]&[OUT]:[TConfViewChgNtf] conference view format(layout geometry)change notify
        
        H_CASCADE_PARTMEDIACHAN_REQ		= 29,   //[IN]&[OUT]:[TPartMediaChanReq] ��������Ա��/�ر���/��Ƶ/����ͨ��
        H_CASCADE_PARTMEDIACHAN_RSP		= 30,   //[IN]&[OUT]:[TRsp]    response
        H_CASCADE_PARTMEDIACHAN_NTF		= 31,   //[IN]&[OUT]:[TPartMediaChanNtf] �����Ա����/��Ƶ/����ͨ����/�رյ�֪ͨ

        H_CASCADE_GETMCUSERVICELIST_REQ = 32,	//[IN]&[OUT]:[TReq] ��ȡMCU�ϵķ���ģ���б��������Ϣ
		H_CASCADE_GETMCUSERVICELIST_RSP	= 33,	//[IN]&[OUT]:[��ʱδ����]  response

		H_CASCADE_GETMUCCONFLIST_REQ	= 34,	//[IN]&[OUT]:[TMCUConfListReq] ��ȡMCU�ϵ�ǰ�ٿ������л�����б�
		H_CASCADE_GETMUCCONFLIST_RSP	= 35,	//[IN]&[OUT]:[��ʱδ����]
  
        H_CASCADE_GETCONFGIDBYNAME_REQ	= 36,	//[IN]&[OUT]:[TGetConfIDByNameReq] ͨ���������ֻ�û���ID��������Ϣ
        H_CASCADE_GETCONFGIDBYNAME_RSP	= 37,	//[IN]&[OUT]:[��ʱδ����]
		
        H_CASCADE_GET_CONFPROFILE_REQ	= 38,	//[IN]&[OUT]:[TConfProfileReq] ��ȡMCU�ϵ�ǰ�ٿ������л����profile
		
        H_CASCADE_GET_CONFPROFILE_RSP	= 39,	//[IN]&[OUT]:[��ʱδ����]

        H_CASCADE_NONSTANDARD_REQ		= 40,	//[IN]&[OUT]:[TNonStandardReq] �Ǳ�(�Զ���)������Ϣ
        H_CASCADE_NONSTANDARD_RSP		= 41,	//[IN]&[OUT]:[TNonStandardRsp] �Ǳ�(�Զ���)response��Ϣ
		H_CASCADE_NONSTANDARD_NTF		= 42,	//[IN]&[OUT]:[TNonStandardMsg] �Ǳ�(�Զ���)notify��Ϣ
		//
        H_CASCADE_NOT_SUPPORTED			= 43,
		//Ŀǰ���ǻ���֧��,����radmuc֧�ֵ���Ϣ����
        H_CASCADE_VA_REQ				= 44,       //[IN]&[OUT]:[TVAReq]
        H_CASCADE_VA_RSP				= 45,       //[IN]&[OUT]:[TRsp]

        H_CASCADE_RELEASECONTROL_OF_CONF_REQ = 46,	//[IN]&[OUT]:[]
        H_CASCADE_RELEASECONTROL_OF_CONF_RSP = 47,	//[IN]&[OUT]:[]

        H_CASCADE_TAKECONTROL_OF_CONF_REQ	 = 48,	//[IN]&[OUT]:[]
        H_CASCADE_TAKECONTROL_OF_CONF_RSP	 = 49,	//[IN]&[OUT]:[]

        H_CASCADE_ALLPART_SETOUT_REQ	= 50,	//[IN]&[OUT]:[]
        H_CASCADE_ALLPART_SETOUT_RSP	= 51,	//[IN]&[OUT]:[]
        
        H_CASCADE_CREATE_CONF_REQ		= 52,	//[IN]&[OUT]:[]
        H_CASCADE_CREATE_CONF_RSP		= 53,	//[IN]&[OUT]:[]
        
        H_CASCADE_TERMINATE_CONF_REQ	= 54,	//[IN]&[OUT]:[]
        H_CASCADE_TERMINATE_CONF_RSP	= 55,	//[IN]&[OUT]:[]

        H_CASCADE_UNDEFINED_REQ			= 56,	//[IN]&[OUT]:[]
        H_CASCADE_UNDEFINED_RSP			= 57,	//[IN]&[OUT]:[]
        H_CASCADE_UNDEFINED_NTF			= 58,	//[IN]&[OUT]:[]

        //add 2007.04.28
        H_CASCADE_SET_LAYOUT_AUTOSWITCH_REQUEST  = 59,	//[IN]&[OUT]:TSetLayoutAutoswitchReq
        H_CASCADE_SET_LAYOUT_AUTOSWITCH_RESPONSE = 60,
        
        CASCADE_MSGTYPE_ENDING = 61
};

#endif //_H323CONFNONSTDMSG_H
