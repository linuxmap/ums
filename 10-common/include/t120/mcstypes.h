#ifndef _MCS_TYPES_H
#define _MCS_TYPES_H

#include <list>
#include <mcspdu2.h>
#include <kdvtype.h>

#define MCS_MAX_TC_CONNECTIONS      (s32)4      // ���TC������
#define MCS_MAX_STATIC_CHANNELID    (s32)1000   // ��̬�ŵ�ID���ֵ
#define MCS_MAX_CHANNELID           (s32)65535  // �ŵ�ID���ֵ
#define MCS_MIN_TOKENID             (s32)1      // ����ID��Сֵ $$$$$ 16384
#define MCS_MAX_TOKENID             (s32)65535  // ����ID���ֵ

// �������ȼ�
typedef enum 
{
    DpTop       = 0,
    DpHigh      = 1,
    DpMedium    = 2,
    DpLow       = 3,
    DpLastPriority
} TDataPriority;

// ���Ƶ�״̬
typedef enum 
{
    TkNotInUse          = 0,
    TkSelfGrabbed       = 1,
    TkOtherGrabbed      = 2,
    TkSelfInhibited     = 3,
    TkOtherInhibited    = 4,
    TkSelfRecipient     = 5,
    TkSelfGiving        = 6,
    TkOtherGiving       = 7
} TTokenStatus;

// SendData/UniformSendʱ���ݶα�־
typedef enum
{
    SgBegin,
    SgEnd
} TSegmentation;

// PDU�е�Resultλ����
typedef enum 
{
	RtSuccessFull		    =  0, // �ɹ�
	RtDomainMerging		    =  1, // Domian �ںϲ���
	RtDomainNotHierarchical	=  2, // Domian ���ֵȼ�
	RtNoSuchChannel		    =  3, // �ŵ�������
	RtNoSuchDomain		    =  4, // Domian ������
	RtNoSuchUser		    =  5, // ���Ʋ�����
	RtNotAdmitted		    =  6, // ���������˽���ŵ�,���߲���Manager
	RtOtherUserId		    =  7,
	RtParametersUnacceptable=  8, // ������������
	RtTokenNotAvaiable	    =  9, // ������Ч
	RtTokenNotPossessed	    = 10, // ����û�б�����
	RtTooManyChannels	    = 11, // �ŵ�����
	RtTooManyTokens		    = 12, // ���ƹ���
	RtTooManyUsers		    = 13, // �û�����
	RtUnspecifiedFailure	= 14, // δָ���Ĵ���
	RtUserRejected		    = 15  // �û����ܾ�
} TResult;

// PDU�е�Reasonλ����
typedef enum 
{
    RnDomainDisconnect	= 0,
    RnProviderInitiated	= 1,
    RnTokenPurged		= 2,
    RnUserRequested		= 3,
    RnChannelPurged		= 4
} TReason;

// PDU��Tagλ����
typedef enum
{
    PduPlumbDomainIndication        =  0, // 
    PduErectDomainRequest           =  1, // 
    PduMergeChannelsRequest         =  2, // 
    PduMergeChannelsConfirm         =  3, // 
    PduPurgeChannelsIndication      =  4, // 
    PduMergeTokensRequest           =  5, // 
    PduMergeTokensConfirm           =  6, // 
    PduPurgeTokensIndication        =  7, // 
    PduDisconnectProviderUltimatum  =  8, // 
    PduRejectMCSPDUUltimatum        =  9, // 
    
    PduAttachUserRequest            = 10, // �����û�����
    PduAttachUserConfirm            = 11, // �����û�ȷ��
    PduDetachUserRequest            = 12, // ɾ���û�����
    PduDetachUserIndication         = 13, // ɾ���û�ȷ��

    PduChannelJoinRequest           = 14, // �����ŵ�����
    PduChannelJoinConfirm           = 15, // �����ŵ�ȷ��
    PduChannelLeaveRequest          = 16, // �뿪�ŵ�����
    PduChannelConveneRequest        = 17, // �ټ�˽���ŵ�����
    PduChannelConveneConfirm        = 18, // �ټ�˽���ŵ�ȷ��
    PduChannelDisbandRequest        = 19, // ��ɢ˽���ŵ�����
    PduChannelDisbandIndication     = 20, // ��ɢ˽���ŵ�ָʾ
    PduChannelAdmitRequest          = 21, // �����û������ŵ�����
    PduChannelAdmitIndication       = 22, // �����û������ŵ�ȷ��
    PduChannelExpelRequest          = 23, // 
    PduChannelExpelIndication       = 24, // 

    PduSendDataRequest              = 25, // Send��ʽ������������
    PduSendDataIndication           = 26, // Send��ʽ��������ָʾ
    PduUniformSendDataRequest       = 27, // Uniform Send��ʽ������������
    PduUniformSendDataIndication    = 28, // Uniform Send��ʽ��������ָʾ
    
    PduTokenGrabRequest             = 29, // 
    PduTokenGrabConfirm             = 30, // 
    PduTokenInhibitRequest          = 31, // 
    PduTokenInhibitConfirm          = 32, // 
    PduTokenGiveRequest             = 33, // 
    PduTokenGiveIndication          = 34, // 
    PduTokenGiveResponse            = 35, // 
    PduTokenGiveConfirm             = 36, // 
    PduTokenPleaseRequest           = 37, // 
    PduTokenPleaseIndication        = 38, // 
    PduTokenReleaseRequest          = 39, // 
    PduTokenReleaseConfirm          = 40, // 
    PduTokenTestRequest             = 41, // 
    PduTokenTestConfirm             = 42  // 
    
} DomainPduTypes;	

// Domain����
typedef struct DomainParameters 
{
    DomainParameters();
    DomainParameters(int, int, int, int, int, int, int, int);

    DomainParameters &operator=(const DomainParameters &); //��ֵ

    bool operator==(const DomainParameters &) const; //�ж�Domain�����Ƿ���ͬ
    bool operator!=(const DomainParameters &) const; //�ж�Domain�����Ƿ�ͬ
    void Truncate(); // �������/��Сֵ���Ʋ���
	void ToProtocol(MCS_PROTOCOL_DomainParameters &) const; // �õ�Э������
    void FromProtocol(const MCS_PROTOCOL_DomainParameters &cProtocol); // ��Э�����ݵõ�����
    void Negotiate(const MCS_PROTOCOL_DomainParameters &cProtocol); // ����Э�����ݽ�������������
    void Negotiate(const DomainParameters &cDomaimPara); // ����DomainPara���ݽ�������������


    unsigned m_maxChannelIds; //���Channel��
    unsigned m_maxUserIds; //���User��
    unsigned m_maxTokenIds; //���token��
    unsigned m_numPriorities; //���ȼ���
    unsigned m_minThroughput; //��СThroughput
    unsigned m_maxHeight; //������߶�
    unsigned m_maxMCSPDUsize; //���MCS Pdu��С
    unsigned m_protocolVersion; //Э��汾
} TDomainParameters;

static DomainParameters cDefaultDomainPara(1024,1024,1024,1,0,16,4128,2);
static DomainParameters cMinDomainPara(1,1,1,1,0,1,1056,2);
static DomainParameters cMaxDomainPara(65535,65535,65535,4,0,100,8121,2);

typedef struct AvaiableDomainParameters 
{
	AvaiableDomainParameters(const DomainParameters & = cDefaultDomainPara,
        const DomainParameters & = cMinDomainPara, 
        const DomainParameters & = cMaxDomainPara);
	
	DomainParameters m_target;
	DomainParameters m_minimum;
	DomainParameters m_maximum;
} AvaiableDomainParameters;

// ����������Quality of Service�����������ƣ�
typedef u32 TQos;


typedef s32 TUserId;
typedef s32 TChannelId;
typedef s32 TTokenId;

class CMcsConnection;
class CMcsUserChannel;
class CMcsChannel;
class CMcsToken;

typedef std::list<CMcsConnection*> TMcsConnectionList;
typedef std::list<CMcsUserChannel*> TUserList;
typedef std::list<TUserId> TUserIdList;
typedef std::list<TChannelId> TChannelIdList;
typedef std::map<TChannelId, CMcsChannel*> TMcsChannelMap;
typedef std::map<TTokenId, CMcsToken*> TMcsTokenMap;


#endif // _MCS_TYPES_H


