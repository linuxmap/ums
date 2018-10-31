#ifndef TPMODULESTRUCT_H
#define TPMODULESTRUCT_H
#include "pastruct.h"

#define     TPMODULE_MAX_NAME_LEN             64            //���������
#define     TPMODULE_REGNAME_SIZE			  64            //ע���������
#define     TPMODULE_MAX_PASSWORD_LEN         16            //������󳤶�
#define     TPMODULE_INVALID_VALUE            -1            //����s32����Чֵ  


enum EmPAEndpointType
{
	emPAEndpointTypeUnknown  = 0,
	emPAEndpointTypeCNS	     = 0x01,
	emPAEndpointTypeUMS		 = 0x02,
	emPAEndpointTypeRegister = 0x04
};


enum EmPASipLevel
{
	emPASipCounty,
	emPASipCity,
	emPASipProvince,
	emPASipUnKnown = 255,
};

enum EmPACapSign    //������ʶ�� ������
{
	emPACapBig = 0,  
	emPACapLeft,
	emPACapSmall = emPACapLeft,  //������ʶ��ԭ���Ĵ�����ת���ɴ�С��
	                             //ö��ֻ��0,1,2��ԭ�������൱��С�����൱�ڽ���
	emPACapRight,
	emPACapEnd = emPACapRight,
};

enum EmPAAddrType
{
	emPAUnknown =0,
	emPAAlias,
	emPAE164Num,
	emPAIPAddr,
	emPAIP6Addr,
	emPADomain,
};

enum EmPAConnection
{
	emPAConnectionType = 0,
	emPATcpConnection,
	emPAUdpConnection,
	emPASCTPConnection,
	emPATLSConnection,
};

typedef struct tagPARegistLocalInfo
{
	EmPAEndpointType  m_emEndpointType;				  //������ums��cns
	u32 m_dwLocalIP;								  //����IP��ַ
	s8  m_achSoftVersion[TPMODULE_MAX_NAME_LEN + 1];  //����汾��
	s8  m_achCompileTime[TPMODULE_MAX_NAME_LEN + 1];  //����ʱ��
public:
    tagPARegistLocalInfo() {memset(this, 0, sizeof(tagPARegistLocalInfo));}
}TPARegistLocalInfo, *PTPARegistLocalInfo;


typedef struct tagPARegName
{
	EmPAAddrType m_emPAAddrType;                      //ע������type
	s8  m_achUserName[TPMODULE_MAX_NAME_LEN + 1];     //ע����
	tagPARegName()
	{
		memset( this, 0, sizeof(tagPARegName) );
	}
}TPARegName, *PTPARegName;

typedef struct tagPARegCfg
{
	u32      m_dwHostIP;		 //ע������IP��ַ
	u16      m_wHostPort;      //ע�������˿�
	u32      m_dwRegIP;        //ע�������IP��ַ
	u16      m_wRegPort;	     //ע��������˿�
	u16      m_wExpire;

	s32		           m_nPARegNameSize;                             //ʵ�ʱ�������
	TPARegName         m_atPARegName[TPMODULE_REGNAME_SIZE];         //ע�����֧�ֶ��
	TPARegistLocalInfo m_tRegistLocalInfo;
	EmPAConnection	   m_emConnection;								 //ע���ַ����
#ifdef _ENABLE_QUANTUM_PROJECT_
	u32		m_dwQtID;	//���Ӽ���ע���ʶ[quantum]
#endif
	tagPARegCfg()
	{
		memset( this, 0, sizeof(tagPARegCfg) );
		m_emConnection = emPAUdpConnection;
	}
}TPARegCfg, *PTPARegCfg;


//������ж���Ĳ���
typedef struct tagCallInfoTP
{
	//EmPAEndpointType		  m_emEndpointType;
	EmPASipLevel			  m_emSipLevel;
	s32                       m_nScreenNum;                           //������
	
public:
	tagCallInfoTP()
	{
		Clear();
	}
	
	void Clear()
	{
		//m_emEndpointType = emPAEndpointTypeUnknown;
		m_emSipLevel = emPASipUnKnown;
		m_nScreenNum = TPMODULE_INVALID_VALUE;
	}
}TCallInfoTP;


//ר����������Ĳ���
typedef struct tagDescriptTP
{
	BOOL32 m_bAudMix;
	s32	m_nScreenNo;                //�����
	s32	m_nPACapSignNum;
	EmPACapSign m_aemPACapSign[MAX_TP_STREAM_NUM];				 //��ʶ��С����, ����������ʱһ��Ҫ����˳�� ���У��� 
	TModuleTransportAddress m_atRtpAddr[MAX_TP_STREAM_NUM];
	TModuleTransportAddress m_atRtcpAddr[MAX_TP_STREAM_NUM];
	
	void Clear()
	{
		m_bAudMix = FALSE;
		m_nScreenNo = TPMODULE_INVALID_VALUE;
		m_nPACapSignNum = 0;
		for ( s32 i = 0; i < MAX_TP_STREAM_NUM; i++ )
		{
			m_aemPACapSign[i] = emPACapBig;
			m_atRtpAddr[i].Clear();
			m_atRtcpAddr[i].Clear();
		}
	}

	tagDescriptTP()
	{
		Clear();
	}
}TDescriptTP;

//��Ӧ��ÿһ������
typedef struct tagCallDescriptTP
{
	u16 m_wAudioNum;
	TDescriptTP m_tAudioList[MAX_AUDIO_NUM];     
	u16 m_wVideoNum;
	TDescriptTP m_tVideoList[MAX_VIDEO_NUM];

	tagCallDescriptTP()
	{
		Clear();
	}
	
	void Clear()
	{
		m_wAudioNum = 0;
		m_wVideoNum = 0;
		s32 i = 0;
		for ( i = 0; i < MAX_AUDIO_NUM; i++ )
		{
			m_tAudioList[i].Clear();
		}
		for ( i = 0; i < MAX_VIDEO_NUM; i++ )
		{
			m_tVideoList[i].Clear();
		}
	}

}TCallDescriptTP;

typedef struct tagChanDescriptTP
{
	TDescriptTP m_tLocalTP; //����TP����
	TDescriptTP m_tPeerTP;  //�Զ�TP����

	tagChanDescriptTP()
	{
		m_tLocalTP.Clear();
		m_tPeerTP.Clear();
	}

}TChanDescriptTP;

enum EmPAConfMsgType
{
	  emPAConfMsgTypeBegin = 0,

		emPAChanMsgBegin = 1,
		emPAConfFastUpdate,                 //NULL
		emPAConfFlowCtrl,                   //wBitRate
		emPAChanMeetingSpeaker,             //cns->ums �᳡�ڷ�����
		emPAChanSelecteCascad,              //add-by wuhu cns��umsָ��ѡ��, ���� u16,��ʾ�᳡id
		emPAChanSelecteCascadRes,           //ums�ظ�cnsѡ������� TPAChanSelecteCascadRes, ��ʾ���
    emPAChanSelecteCascadCancel,        //ȡ��ѡ�����޲���
		emPAChanSelecteCascadCancelRes,     //ȡ��ѡ�������  ����u32, ��ʾ��� 
		emPAChanSeeLocal,                   //ums -> cns, �����أ��޲���
		emPAChanSeeLocalCancel,             //ums -> cns  ȡ�������أ��޲���
		emPAChanMsgEnd = 160,

		emPAConfMsgBegin = 161,
		emPAConfYouAreSeeing,               //TYouAreSeeing ������ָʾ
		emPAYouAreSeeing_v2,			    //TPAYouAreSeeing
		emPAConfBeChairman,                 //BOOL ums->cns ��Ϊ��ϯ
		emPAConfCascadingSpeaker,           //TPACascadingSpeaker �������� �����᳡�ڷ�����
		emPAConfStartPoll,                  //TPAPollCmd �������� ������ѯ
		emPAConfStartPollAck,               //TPAPollAck
		emPAConfPollNodeChange,             //TPAPollNodeChange ��������
		emPAConfEndPoll,                    //u32(Reserved)
		emPAConfPollFastUpdate,             //��������u32(Reserved)
		emPAConfStatusIndicate,             //TPAConfStatusInd , ums->cns
		emPAConfPeerMuteCmd,                //Զ������  TPAPeerMuteCmd
		emPAConfPeerMuteInd,                //Զ������״ָ̬ʾ TPAPeerMuteInd
		emPAConfCallCascadingOff,           //�����¼�δ���߻᳡ u16 epid
		emPAConfHangUpCascadingConf,        //�Ҷ��¼����� THangupCascadingConf
		emPAConfNodeUpdateTrList,           //֪ͨ���½����Ϣ TPAConfNodeUpdateTrList
		emPAConfNodeUpdateB2NewTrList,      //֪ͨ���½����Ϣ TPAConfNodeUpdateB2NEWTrList
		emPAConfNodeDelTrList,              //֪ͨɾ����� TPAConfNodeDelTrList
		emPAConfAudMixEpCmd,                //�ϼ�֪ͨ�¼�����ĳ���˵�  TPAAudMixEpCmdTr
		emPAConfAudMixEpAck,                // �¼�֪ͨ�ϼ�����ĳ���˵�Ľ�� TPAAudMixEpAckTr
		emPAConfAudMixEpStop,               // �ϼ���֪ͨ�¼�ֹͣĳ���˵�Ļ��� u16
		emPAConfAudMixOpenNCmd,             // �ϼ�֪ͨ�¼���Nģʽͨ�� TPAAudMixEpCmdTr
		emPAConfAudMixOpenNAck,             // �¼�֪ͨ�ϼ���Nģʽͨ�� TPAAudMixEpAckTr
		emPAConfPeerSoundOffCmd,            //Զ�˾��� TPAPeerMuteCmd
		emPAConfPeerSoundOffInd,            //Զ�˾���ָʾ TPAPeerMuteInd
		emPARequestDualStreamCmd,           //����˫�� TDualRequest
		emPARequestDualStreamInd,           //����˫��ָʾ BOOl + EmDualReason + TDualRequest
		emPASendDualStream,                 //��˫�� TDualInfo
		emPASendDualStreamAck,              //��˫����� TDualInfoAck
		emPAStopDualStream,                 //ֹͣ˫�� TPAEpKey
		emPADualStreamFastUpdate,           //˫���ؼ�֡���� BOOL32ֵ
		emPAViewLocal,                      //������ u32(Reserved)
		emPACancelViewlocal,                //ȡ�������� u32(Reserved)
		emPAStartRcvDualInd,                //����˫��ָʾTPAEpKey
		emPAStopRcvDualInd,                 //ֹͣ����˫��ָʾEmDualReason
		emPAAddTvMonitorCmd,                //����ǽ��� TPATvMonitorCmd 
		emPAAddTvMonitorInd,                //����ǽ��� TPATvMonitorInd 
		emPAStopMonitorCmd,	                //ֹͣ����ǽ�ļ��	u16
		emPAAskKeybyScreen,                 //ֹͣ����ǽ�ļ��	TPAAskKeyByScreenTr
		emPAPollDstNameInd,                 //֪ͨ��ѯĿ����Ϣ ,TPAPollDstName
		emPASrcDualNameInd,                 //֪ͨ˫��Դ��Ϣ TPAName
		emPAChairCapNotify,                 //֪ͨ�¼���ϯ��ϯ����
		emPAConfCnsList,                    // UMS��CNS���᳡�б�,   ������ TPAConfCnsList;
		emPAConfStartPolling,               //cns��ums������ѯ,  �޲��������贫���������u32ֵ
    emPAConfStartPollingRes,            //ums��Ӧcns��ѯ���, ������u32
		emPAConfClosePolling,               //cns��ums�ر���ѯ,   �޲��������贫���������u32ֵ
		emPAConfClosePollingRes,            //ums��cns��Ӧ�ر���ѯ���,  ���� u32
		emPAConfNotifyPollingRes,           //ums֪ͨcns��ǰ��ѯ���,   ���� BOOL32
		emPACascadeStartViewcmd,	          //�ϼ�֪ͨ�¼�ѡ��ĳ���᳡ TPAViewCmd
		emPACascadeStartViewInd,	          //�¼�֪ͨ�ϼ�ѡ��ĳ���᳡��� TPAViewAck
		emPACascadeStopView_cmd,	          //�ϼ�֪ͨ�¼�ֹͣĳ��ѡ��	u16
		emPACascadeGetVidcmd,	              //�ϼ������¼�ͼ�� TPAViewCmd
		emPACascadeGetVidInd,	              //�¼������¼�ͼ���� TPAViewAck
		emPACascadeStopGetVidcmd,	          //�ϼ�ֹ֪ͨͣ�¼�����	u16
		emPACascadeFlowCtrl,		            //�ϼ�֪ͨ�¼�flowctrl�� ����TPAFlowControl
		
		emPAOpenAudChanCmd,                 //����Ƶͨ��           TPAAudChanCmd
		emPAOpenAudChanAck,                 //����Ƶͨ��Ӧ��       TPAAudChanAck
		emPAOpenVidChanCmd,                 //����Ƶͨ��           TPAVidChanCmd
		emPAOpenVidChanAck,                 //����Ƶͨ��Ӧ��       TPAVidChanAck
		emPACloseVidChanCmd,                //�ر���Ƶͨ��           u16+u32
		
		emPATpConfAMixUpdate_Cmd,           //�����鿪��           TPAConfAuxMixInfo
		emPATpConfAMixUpdate_Ind,           //�������Ӧ           TPAConfAuxMixInfo
		emPATpConfAMixUpdate_Nty,           //���������ۿ���֪ͨ   TPAConfAuxMixInfo
		
		emPATpConfApplySpeaker_Cmd,         //�������л�������     TPAConfEpID
		emPATpConfApplySpeaker_Ind,         //�������л������˻�Ӧ TPAConfEpID,  EmPATpApplySpeakerRet 
		emPATpConfApplySpeaker_Nty,         //�������л�������֪ͨ TPAConfEpID
		
		emPATpConfMute_Cmd,                 //���������Զ������      TPAConfEpID, BOOL,  TRUEָʾԶ��������FALSEȡ��Զ������
		emPATpConfMute_Ind,                 //���������Զ��������Ӧ  TPAConfEpID, BOOL,  TRUEָʾԶ��������FALSEȡ��Զ������
		emPATpConfMute_Nty,                 //���������Զ������֪ͨ  TPAConfEpID, BOOL,  TRUEָʾԶ��������FALSEȡ��Զ������

		emPATpConfQuiet_Cmd,                //���������Զ�˾���        TPAConfEpID, BOOL,  TRUEָʾԶ��������FALSEȡ��Զ������
		emPATpConfQuiet_Ind,		            //���������Զ�˾�����Ӧ    TPAConfEpID, BOOL,  TRUEָʾԶ��������FALSEȡ��Զ������
		emPATpConfQuiet_Nty,                //���������Զ�˾���֪ͨ    TPAConfEpID, BOOL,  TRUEָʾԶ��������FALSEȡ��Զ������
		
		emPATpConfStartDual_Cmd,            //������˫������          TPAConfEpID   
		emPATpConfStartDual_Ind,            //������˫������Ӧ��      TPAConfEpID,  EmPATPDualReason
		emPATpConfStopDual_Cmd,             //������ͣ˫������        TPAConfEpID
		emPATpConfStopDual_Ind,             //������ͣ˫������Ӧ��    TPAConfEpID,  EmPATPDualReason
		emPATpConfDualEp_Nty,               //������˫���᳡�㲥֪ͨ  TPAConfEpID

		emPATpInviteCnsByAlias_Cmd,         //��������ͨ�����������б��в����ڵĻ᳡          TPACallAddr
		emPATpInviteCnsByAlias_Ind,         //��������ͨ�����������б��в����ڵĻ᳡��Ӧ      TPACallAddr, EmPACnsCallReason
		emPATpInviteCnsByEpId_Cmd,          //��������ͨ�����ֺ����б��д��ڵĲ����߻᳡      u16 wEpId
		emPATpInviteCnsByEpId_Ind,          //��������ͨ�����ֺ����б��д��ڵĲ����߻᳡��Ӧ  u16 wEpId, EmPACnsCallReason
	
		emPATpHangupCns_Cmd,                 //���Ҷ�ָ���᳡         u16 wEpId
		emPATpHangupCns_Ind,                 //���Ҷ�ָ���᳡��Ӧ     u16 wEpId, EmPACnsCallReason
		emPATpHangupConf_Cmd,                //�Ҷϻ���                 �޲������贫���������u32ֵ
		
		emPATpUpdateConfTurnlist_Nty,        //��ѯ�б�֪ͨ           TPAConfTurnInfo
		emPATpCallEPResult_Ind,              //���н����           TPAConfCallEpAddr, EmPACnsCallReason,  
		emPATpChairConfInfo_Nty,             //֪ͨ��ϯ������Ϣ       TPAChairConfInfo
		emPATpAudMixStatus_Nty,              //�᳡��������״̬֪ͨ   TPAAudMixStat

		emPAAdjustFrameRate_Cmd,             //TPAAdjustFrameRate
		emPAAdjustVidRes_Cmd,                //TPAAdjustVidRes
		
		emPAUmsDiscussScreenStat_Notify,     //����ģʽ�еĻ᳡����Ҫ�յ�����״̬֪ͨ, TPADisScreenStat 
		emPAUmsCnsSpeakerIndxAdjust_Notify,  //TPACascadingSpeaker
		
		emPAUmsDiscussFastUpdate_Req,        /*����Դ�᳡ID������ţ��Ϳ���ͨ��AskKeyByScreen����Ŀ��᳡�ķ���������ؼ�֡
		                                        TPADisAskKeyFrame */
		emPAUmsAudMixDisListOpr_Cmd,         //CNC -> CNS -> UMS, TPADisListOpr
		emPAUmsAudMixDisListOpr_Ind,         //UMS -> CNS -> CNC, TPADisListOpr

		emPAUmsCascadeOpenChairChan_Cmd,     // UMS �������� ����ϯͨ������, TPACascadeOpenChanCmd
		emPAUmsCascadeOpenChairChan_Ack,     // UMS �������� ����ϯͨ��Ӧ��, TPACascadeOpenChanAck

		emPAUmsCommonReasonToUI_Ind,         // ��Ϣ����: ums -> cns -> cnc, ��Ϣ����: TPAUmsReasonInd

    emPAUmsConfRecPlayState_Nty,         // ���·���״̬, ��Ϣ����: TPAUmsUpRecPlayState
    emPAUmsConfStopRecPlay_Req,          // ֹͣ�¼��ķ����޲��������贫���������u32ֵ
		
		emPAChanResetFastUpdate,				     //ͨ����Ϣ������ȥ��ums�Ĺؼ�֡������u32
		emPAJoinWBConf_Cmd,						       //��Ϣ�壺U32 dwDsIPAddr
		emPAJoinWBConf_Ind,					         //��Ϣ�壺BOOL bIsSucc
		emPAHangupWBConf_Cmd,			          //��Ϣ�壺Null

		emPAVMPOpr_Cmd,						//����/�رջ���ϳ�, ��Ϣ�壺TTPVMPInfo
		emPAVMPOpr_Ind,						//����/�رջ���ϳ�, ��Ϣ�壺TTPVMPInfo

		emPAChanSelecteVMPView,             //ѡ������ϳ�, �޲���
		emPAChanSelecteVMPViewRes,          // ѡ������ϳ�, u32,ѡ�����
		
		emPAChanSelecteVMPViewCancel,		//ȡ��ѡ������ϳ�,�޲���
		emPAChanSelecteVMPViewCancelRes,	//ȡ��ѡ������ϳ�, u32,ȡ��ѡ�����
		emPACNC_UMS_SelView_Req,			//TPATPSelViewReq
		emPAUMS_CNC_SelView_Ind,			//TPATPSelViewInd
		emPAUMS_UMC_SelView_Ntfy,			//TPASelViewNtfy
		
		emPAGetVid_Req,                     //TPAUmsHandle,TPAGetVidInfo
		emPAGetVid_Res,						//TPAUmsHandle,TPAGetVidInfoRes
		emPAGetVid_Stop_Req,				//TPAUmsHandle,TPAGetVidBaseInf
		emPAGetVid_Stop_Res,				//TPAUmsHandle,TPAStopGetVid

		emPAConf_SuspendPoll_Req,			//BOOL32
		emPAConf_SuspendPoll_Ind,			//u32
		emPAConf_CasecadePollEp_Req,		//TPACasecadePollEpReq
		emPAConf_CasecadePollEp_Rsp,		//TPACasecadePollEpRsp

		emPAUmsUpdateConfTurnlist_Ind,		//TPAPollListInd

		emPACNC_UMS_RervesBrdVmp_Req,       //TPARersvesEqpReq
		emPAUMS_CNC_RervesBrdVmp_Ind,		//TPARersvesEqpRsp
		emPACNC_UMS_SetBrdVmp_Req,			//TPASetVmpInfoReq
		emPAUMS_CNC_SetBrdVmp_Ind,			//TPASetVmpInfoRsp
		emPACNC_UMS_BrdVmp_Req,				//TPABrdVmpReq
		emPAUMS_CNC_BrdVmp_Ind,				//TPABrdVmpRsp
		emPAUMS_UMS_VmpCasecade_Ntfy,		//TPAVmpCasecadeNtfy
		emPAUMS_CNC_BrdVmp_Ntfy,			//TPABrdVmpResArray 

		emPAUmsConfAMixVacSwitch,			//�������������͹ر�      cns->ums   TPAConfAuxMixVacOpr
		emPAUmsConfAMixVacSwitchInd,		//�������������͹رջ�Ӧ  ums->cns	  TPAConfAuxMixVacOpr
		emPACNC_UMS_SaveVmpCfg_Cmd,			//TPAVmpMemberCfg
		emPAUMS_CNC_SaveVmpCfg_Ind,			//TPAVmpMemberCfgInd

		emPA_CnsJoinConf_Req,				//TPAConfEpInfo
		emPA_CnsJoinConf_Ack,				//TPAConfEpInfo

		emPACnsJoinConf_Notify,				//u16 TPACallAddr
		emPAUMS_CNS_HduPlan_Nty,			//TPAHduPlanPackData  �����Ϣ���÷ְ����ͣ���ע��
		emPACNS_UMS_HduPlay_Req,			//TPAHduPlayReq
		emPAUMS_CNS_HduPlay_Ind,			//TPAHduBaseInfo EmPAHduPlayNackReason
		emPACNS_UMS_HduStopPlay_Req,		//TPAHduPlayReq
		emPAUMS_CNS_HduStopPlay_Ind,		//TPAHduBaseInfo u16(�����룬0�ɹ�������ʧ��)
		emPACNS_UMS_HduAllStopPlay_Req,		//u32
		emPACNS_UMS_HduSetVol_Req,			//TPAHduSetVolInfo
		emPAUMS_CNS_HduSetVol_Ind,			//TPAHduSetVolInfo EmPAHduSetVolRes
		emPACNS_UMS_HduChangeChanMode_Req,	//TPAHduChanModeSetInfo
		emPAUMS_CNS_HduChangeChanMode_Ind,	//TPAHduChanModeSetInfo EmPAHduChangeChanModeRes

		emPACNS_UMS_ConfAudMixMode_cmd,    //TPAUmsAudMixInfo
		emPAUMS_CNS_ConfAudMixMode_ind,    //TPAUmsAudMixModeCmdRes
		emPACNS_UMS_ConfAudMixList_cmd,    //TPAUmsAudMixListCmd
		emPAUMS_CNS_ConfAudMixList_ind,    //TPAUmsAudMixListCmdRes
		emPAUMS_CNS_ConfAudMixMode_Notify, //TPAUmsAudMixInfo
		emPAUMS_UMS_ConfAudMixMode_Notify, //TPAUmsAudMixCasecadeInfo

		emPAUmsConfRollCallUpdate_Cmd,    //TPAConfRollCallInfo
		emPAUmsConfRollCallUpdate_Ind,   //TPAConfRollCallInfo
		emPAUmsConfRollCallNextEp_Cmd,   //TPARollCallNextEpInfo
		emPAUmsConfRollCallNextEp_Ind,   //TPARollCallNextEpInfo
		emPAUmsRollCallScreenStat_Notify,//TPARollCallCasecadeNtfy
		emPAUmsConfRollCallUpdate_Nty,  //TPAConfRollCallInfo

		emPAUmsConfRollCallUpdataList_Cmd,//TPAUpdataRollCallList
		emPAUmsConfRollCallUpdataList_Ind,//TPAUpdataRollCallListRes
		emPAUmsRollUpdate_PresentState,//TPARollCallPresentStateMsg
		emPAUmsRoll_PresentState_Notify,//TPARollCallPresentStateMsg
		emPAUMS_CNS_EpInAudMix_Notify,//BOOL32
		
		emPAUMS_CNS_VidFeccInfoNty,//TPAConfVidFeccInfo 
		emPAConf_EpVidFeccInfo_Update,//TConfEpVidFeccList 
		
#ifdef _ENABLE_QUANTUM_PROJECT_
		emPAQuantumMideaKey				//ƽ̨�㲥��������MideaHandle,Э��͸��
#endif
};

typedef struct tagMdlCallCapTP
{
	TCallInfoTP m_tCallInfoTP;
	TCallDescriptTP m_tCallSndTP;
	TCallDescriptTP m_tCallRcvTP;

	tagMdlCallCapTP()
	{
		Clear();
	}

	void Clear()
	{
		m_tCallInfoTP.Clear();
		m_tCallSndTP.Clear();
		m_tCallRcvTP.Clear();
	}

}TMdlTPCap;

enum EmPAGetRegInfoType
{
	emPAGetRegInfoType_CNS = 0,
	emPAGetRegInfoType_UMS,
	emPAGetRegInfoType_ALL
};
typedef struct tagPAGetRegInfo
{
	EmPAGetRegInfoType m_emType;
	u32    m_dwRegIP;         //ע�������IP��ַ
	u16    m_wRegPort;        //ע��������˿�
	u32    m_dwLocalIP;       //����ip
	u16    m_wLocalPort;      //���ض˿�
	
	tagPAGetRegInfo()
	{
		memset( this, 0, sizeof(tagPAGetRegInfo) );
	}
}TPAGetRegInfo;

 
typedef struct tagTPARegPackInfo
{
	u16 m_wPackSeq;       //����ţ���1��ʼ��0Ϊ��Чֵ
	u16 m_wTotalPackNum;  //������
	tagTPARegPackInfo()
	{
		m_wPackSeq = 0;
		m_wTotalPackNum = 0;
	}
	
}TPARegPackInfo, *PTPARegPackInfo;


typedef struct tagTPARegInfo
{
	u16		   m_wAliasNum;
	TPAAlias   m_atAlias[PA_REGNAME_SIZE];           //��ʱ��Ϊ���ֵΪ64������Ϊһ������
	EmPAEndpointType m_emSelfType;                   //ע�᷽ ��ϵͳ����(UMS��CNS)    
	
	tagTPARegInfo()
	{
		m_wAliasNum = 0;
		memset( m_atAlias, 0, sizeof( m_atAlias ) );
		m_emSelfType = emPAEndpointTypeUnknown;
	}
	
}TPARegInfo;

typedef struct tagTPARegInfoUms
{
	u16		  m_wAliasNum;
	TPAAlias  m_atAlias[PA_REGNAME_SIZE];				 //��ʱ��Ϊ���ֵΪ64������Ϊһ������
	TPAIPAddress  m_atContactAddr[PA_CONTACT_ADDR_SIZE]; //ע���ַ
	u32 m_dwExpires;									 //��ʱʱ��,��λ��
	EmPAConnection emPaConnection;
	TPARegistLocalInfo m_tPaRegistLocalInfo;
	
	tagTPARegInfoUms()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTPARegInfoUms));
	}
	
}TPARegInfoUms;

typedef struct tagTPARegInfoCns
{
	u16		   m_wAliasNum;
	TPAAlias   m_atAlias[PA_REGNAME_SIZE_CNS];           //��ʱ��Ϊ���ֵΪ2������Ϊһ������
	TPAIPAddress  m_atContactAddr[PA_CONTACT_ADDR_SIZE]; //ע���ַ
	u32 m_dwExpires;//��ʱʱ��,��λ��
	EmPAConnection emPaConnection;
	TPARegistLocalInfo m_tPaRegistLocalInfo;
	
	tagTPARegInfoCns()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTPARegInfoCns));
	}
	
}TPARegInfoCns;

typedef struct tagTPARegPack
{
	TPARegPackInfo m_tPackInfo;
	EmPAGetRegInfoType m_emType;
	EmPAEndpointType  m_emEndpointType;
	u16	m_wTotalRegInfo;

	tagTPARegPack()
	{
		Clear();
		m_emType = emPAGetRegInfoType_ALL;
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTPARegPack));
	}

}TPARegPack;




#endif
