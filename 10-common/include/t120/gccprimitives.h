/******************************************************************************
ģ����      ��GccPrimitives
�ļ���      ��GccPrimitives.h
����ļ�    ��GccPrimitives.cpp
�ļ�ʵ�ֹ��ܣ���������GCCԭ��
����        ������
�汾        ��4.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �߶���      �޸�����
24/05/05    4.0         ����        ����        ����
******************************************************************************/
#ifndef _GCC_PRIMITIVES_H_
#define _GCC_PRIMITIVES_H_

#include <mqm.h>
#include <gcctypes.h>
#include <gccregistry.h>

using namespace Gcc;

typedef u8 TApeId;

// Gcc��Ϣ����(С)����
typedef enum
{
    // ����Gcc����ԭ��
    e_StartGccRequest,
    // ����Gccȷ��ԭ��
    e_StartGccConfirm,
    // ����NC��GCCԭ��
    e_NcAttachPrimitive,
    // ����APE��GCCԭ��
    e_ApplicationAttachPrimitive,
    // ɾ��APE��GCCԭ��
    e_ApplicationDetachPrimitive,
    // ������������ԭ��
    e_ConferenceCreateRequest,
    // ��������ȷ��ԭ��
    e_ConferenceCreateConfirm,
    // �����ѯ����ԭ��
    e_ConferenceQueryRequest,
    // �����ѯȷ��ԭ��
    e_ConferenceQueryConfirm,
    // �����������ԭ��
    e_ConferenceJoinRequest,
    // �������ָʾԭ��
    e_ConferenceJoinIndication,
    // �������ظ�ԭ��
    e_ConferenceJoinResponse,
    // �������ȷ��ԭ��
    e_ConferenceJoinConfirm,
    // ������������ԭ��
    e_ConferenceInviteRequest,
    // ��������ָʾԭ��
    e_ConferenceInviteIndication,
    // ��������ظ�ԭ��
    e_ConferenceInviteResponse,
    // ��������ȷ��ԭ��
    e_ConferenceInviteConfirm,
    // ����Ͽ�����ԭ��
    e_ConferenceDisconnectRequest,
    // ����Ͽ�ָʾԭ��
    e_ConferenceDisconnectIndication,
    // ����Ͽ�ȷ��ԭ��
    e_ConferenceDisconnectConfirm,
    // ������������ԭ��
    e_ConferenceTerminateRequest,
    // ��������ָʾԭ��
    e_ConferenceTerminateIndication,
    // ��������ȷ��ԭ��
    e_ConferenceTerminateConfirm,
    // �ҶϽڵ�����ԭ��
    e_ConferenceEjectUserRequest,
    // �ҶϽڵ�ָʾԭ��
    e_ConferenceEjectUserIndication,
    // �ҶϽڵ�ȷ��ԭ��
    e_ConferenceEjectUserConfirm,
    // �����ڵ�����ԭ��
    e_ConferenceAnnouncePresenceRequest,
    // �����ڵ�ȷ��ԭ��
    e_ConferenceAnnouncePresenceConfirm,
    // ����ǼǱ�㱨ָʾԭ�δʹ�ã�
    e_ConferenceRosterReportIndication,
    // �����������ڵ�֪ͨԭ��
    e_ConferenceNodeAddIndication,
    // ������ɾ���ڵ�֪ͨԭ��
    e_ConferenceNodeRemoveIndication,
    // ָ��Ӧ������֪ͨԭ��
    e_ConferenceApeMaskIndication,
    // ����ǼǱ��ѯ����ԭ��
    e_ConferenceRosterInquireRequest,
    // ����ǼǱ��ѯȷ��ԭ�δʹ�ã�
    e_ConferenceRosterInquireConfirm,
    // ����Ӧ�õǼ�ָʾԭ��
    e_ApplicationPermissionToEnrollIndication,
    // Ӧ�õǼ�����ԭ��
    e_ApplicationEnrollRequest,
    // Ӧ�õǼ�ȷ��ԭ��
    e_ApplicationEnrollConfirm,
    // Ӧ�õǼǱ�㱨ָʾԭ�δʹ�ã�
    e_ApplicationRosterReportIndication,
    // ����������Ӧ��֪ͨԭ�� 
    e_ConferenceApeAddIndication,
    // �������޸�Ӧ��֪ͨԭ��
    e_ConferenceApeReplaceIndication,
    // ������ɾ��Ӧ��֪ͨԭ��
    e_ConferenceApeRemoveIndication,
    // Ӧ�õǼǱ��ѯ����ԭ��
    e_ApplicationRosterInquireRequest,
    // Ӧ�õǼǱ��ѯȷ��ԭ��
    e_ApplicationRosterInquireConfirm,
    // ע���ŵ�����ԭ��
    e_RegistryRegisterChannelRequest,
    // ע���ŵ�ȷ��ԭ��
    e_RegistryRegisterChannelConfirm,
    // ����ע����������ԭ��
    e_RegistryAssignTokenRequest,
    // ����ע������ȷ��ԭ��
    e_RegistryAssignTokenConfirm,
    // ��ѯע��������ԭ��
    e_RegistryRetrieveEntryRequest,
    // ��ѯע����ȷ��ԭ��
    e_RegistryRetrieveEntryConfirm,
    // ɾ��ע��������ԭ��
    e_RegistryDeleteEntryRequest,
    // ɾ��ע����ȷ��ԭ��
    e_RegistryDeleteEntryConfirm,
    // ����������ԭ��
    e_RegistryAllocateHandleRequest,
    // ������ȷ��ԭ��
    e_RegistryAllocateHandleConfirm,
    // ָ��������ϯ����(�Ǳ�׼)
    e_AssignConductorRequest,
    // ������������(�Ǳ�׼)
    e_ConfSetFlowControl,
    // �����������(�Ǳ�׼)
    e_ConfFlowControlConfirm
} enumGccMsgType;



/*====================================================================
���� �� CStartGccRequest
���� �� ����Gcc����ԭ��
====================================================================*/
class CStartGccRequest : public CMsg
{
public:
    CStartGccRequest():CMsg(e_Gcc, e_StartGccRequest)
    {
    }

    // ������ַ
    PString m_strAddress;
};


/*====================================================================
���� �� CStartGccConfirm
���� �� ����Gccȷ��ԭ��
====================================================================*/
class CStartGccConfirm : public CMsg
{
public:
    CStartGccConfirm():CMsg(e_Gcc, e_StartGccConfirm)
    {
    }

    // �������
    bool m_bResult;
};


/*====================================================================
���� �� CNcAttachPrimitive
���� �� ����NodeController��GCCԭ��
====================================================================*/
class CNcAttachPrimitive : public CMsg
{
public:
    CNcAttachPrimitive():CMsg(e_Gcc, e_NcAttachPrimitive)
    {
    }

};


/*====================================================================
���� �� CApplicationAttachPrimitive
���� �� ����APE��GCCԭ��
====================================================================*/
class CApplicationAttachPrimitive : public CMsg
{
public:
    CApplicationAttachPrimitive():CMsg(e_Gcc, e_ApplicationAttachPrimitive)
    {
    }

    // ��Ape��SessionKey
    SessionKey m_cSessionKey;
};




/*====================================================================
���� �� CApplicationDetachPrimitive
���� �� ɾ��APE��GCCԭ��
====================================================================*/
class CApplicationDetachPrimitive : public CMsg
{
public:
    CApplicationDetachPrimitive():CMsg(e_Gcc, e_ApplicationDetachPrimitive)
    {
    }

    // ��Ape��SessionKey
    SessionKey m_cSessionKey;
};


/*====================================================================
���� �� CGccConferenceCreateRequest
���� �� ������������ԭ��
====================================================================*/
class CGccConferenceCreateRequest : public CMsg
{
public:
    CGccConferenceCreateRequest():CMsg(e_Gcc, e_ConferenceCreateRequest)
    {
        m_enumQualityOfService = 0;
        m_strUserData.Empty();
    }

    // ����������
    ConferenceDescriptor m_cConferenceDescriptor;
    // �����Ӧ��Mcs����
    TDomainParameters m_cDomainParameters;
    // Qos����
    TQos m_enumQualityOfService;
    // �û�����
    PString m_strUserData;
};


/*====================================================================
���� �� CGccConferenceCreateConfirm
���� �� ��������ȷ��ԭ��
====================================================================*/
class CGccConferenceCreateConfirm : public CMsg
{
public:
    CGccConferenceCreateConfirm():CMsg(e_Gcc, e_ConferenceCreateConfirm)
    {
    }

    // ����������
    ConferenceDescriptor m_cConferenceDescriptor;
    // ��������Ļ���ID
    u32 m_nConferenceID;
    // �û����Ӧ��Domain������Ϣ
    TMessageContext m_tMcsDomain;
    // �����Ӧ��Mcs����
    TDomainParameters m_cDomainParameters;
    // Qos����
    TQos m_enumQualityOfService;
    // �û�����
    PString m_strUserData;
    // �������
    ConferenceResponseResult m_enumResult;
    // �Ƿ񱾵ش���
    bool m_bIsLocalCreate;
};


/*====================================================================
���� �� CConferenceQueryRequest
���� �� �����ѯ����ԭ��
====================================================================*/
class CConferenceQueryRequest : public CMsg
{
public:
    CConferenceQueryRequest():CMsg(e_Gcc, e_ConferenceQueryRequest)
    {
    }

    // �ڵ�����
    NodeType m_enumNodeType;
    // ����ѯ�ڵ�ĵ�ַ
    PString m_strCalledAddress;
};


/*====================================================================
���� �� CConferenceQueryConfirm
���� �� �����ѯȷ��ԭ��
====================================================================*/
class CConferenceQueryConfirm : public CMsg
{
public:
    CConferenceQueryConfirm():CMsg(e_Gcc, e_ConferenceQueryConfirm)
    {
    }

    // ��ѯ���
    ConferenceResponseResult m_enumResult; 
    // �ڵ�����
    NodeType m_enumNodeType;
    // �ýڵ������б��г��Ļ���
    std::list<ConferenceDescriptor> m_listConferenceDescriptorList;
    // ����ѯ�ڵ�ĵ�ַ
    PString m_strCalledAddress;
};


/*====================================================================
���� �� CConferenceJoinRequest
���� �� �����������ԭ��
====================================================================*/
class CConferenceJoinRequest : public CMsg
{
public:
    CConferenceJoinRequest():CMsg(e_Gcc, e_ConferenceJoinRequest)
    {
        m_nConfId = 0;
        m_strPassword.MakeEmpty();
    }

    // ��������
    PString m_strConferenceName;
    // ����ID�����������ƣ�
    u32 m_nConfId;
    // ������������
    PString m_strConfNumericName;
    // �����������η�
    PString m_strCalledNodeConferenceNameModifier;
    // ��������
    PString m_strPassword;
    // ����������
    PString m_strCallerIdentifier;
    // �������������ڽڵ�ĵ�ַ
    PString m_strCalledAddress;
    // �û��������������������ƣ�
    u32 m_nFlowControl;
    // �����Ӧ��Mcs����
    TDomainParameters m_cDomainParameters;
    // Qos����
    TQos m_enumQualityOfService;
    // �û�����
    PBYTEArray m_cUserData;
};


/*====================================================================
���� �� CConferenceJoinIndication
���� �� �������ָʾԭ��
====================================================================*/
class CConferenceJoinIndication : public CMsg
{
public:
    CConferenceJoinIndication():CMsg(e_Gcc, e_ConferenceJoinIndication)
    {
    }

    // ����ID
    u32 m_nConferenceId;
    // ��������
    PString m_strPassword;
    // ����������
    PString m_strCallerIdentifier;
    // �Ƿ�ֱ�Ӽ��뱾�ڵ�
    bool m_bIsLocalJoined;
    // �����ߵ�IP��ַ��ֱ�Ӽ�����Ч����������ʱ�Ǳ�����ڵ���Ϣ��
    PString m_strCallingAddress;
    // �����ߵ�NodeId����������ʱ�Ǳ�����ڵ�NodeId��ֱ�Ӽ���ʱ�Ǳ��ڵ�NodeId��
    TUserId m_nFromNodeId;
    // ����Tag
    u32 m_nTag;
    // �û�����
//    PBYTEArray m_cUserData;
};


/*====================================================================
���� �� CConferenceJoinResponse
���� �� �������ظ�ԭ��
====================================================================*/
class CConferenceJoinResponse : public CMsg
{
public:
    CConferenceJoinResponse():CMsg(e_Gcc, e_ConferenceJoinResponse)
    {
    }

    // ����ID
    u32 m_nConferenceId;
    // ��������
    PString m_strPassword;
    // �û�����
    PBYTEArray m_cUserData;
    // ����Tag, ������ʶ��ͬ������
    u32 m_nTag;
    // ������
    ConferenceResponseResult m_enumResult;
};


/*====================================================================
���� �� CConferenceJoinConfirm
���� �� �������ȷ��ԭ��
====================================================================*/
class CConferenceJoinConfirm : public CMsg
{
public:
    CConferenceJoinConfirm():CMsg(e_Gcc, e_ConferenceJoinConfirm)
    {
    }

    // ����������
    ConferenceDescriptor m_cConferenceDescriptor;
    // ��������Ļ���ID
    u32 m_nConferenceID;
    // ��������
    PString m_strPassword;
    // �����ַ
    PString m_strJoinAddr;
    // �����Ӧ��Mcs����
    TDomainParameters m_strDomainParameters;
    // Qos����
    TQos m_enumQualityOfService;
    // �û�����
    PBYTEArray m_cUserData;
    // ������
    ConferenceResponseResult m_enumResult;
};


/*====================================================================
���� �� CConferenceInviteRequest
���� �� ������������ԭ��
====================================================================*/
class CConferenceInviteRequest : public CMsg
{
public:
    CConferenceInviteRequest():CMsg(e_Gcc, e_ConferenceInviteRequest)
    {
    }

    // ����ID
    u32 m_nConferenceID;
    // ����������
    PString m_strCallerIdentifier;
    // �����ߵ�ַ
    PString m_strCallingAddress;
    // ������ڵ��ַ
    PString m_strCalledAddress;
    // �û�����
    PBYTEArray m_cUserData;
};


/*====================================================================
���� �� CConferenceInviteIndication
���� �� ��������ָʾԭ��
====================================================================*/
class CConferenceInviteIndication : public CMsg
{
public:
    CConferenceInviteIndication():CMsg(e_Gcc, e_ConferenceInviteIndication)
    {
    }

    // ����������
    ConferenceDescriptor m_cConferenceDescriptor;
    // ����ID
    u32 m_nConferenceID;
    // ������
    u32 m_nInviteTag;
    // ����������
    PString m_strCallerIdentifier;
    // �����ߵ�ַ
    PString m_strCallingAddress;
    // �����Ӧ��Mcs����
    TDomainParameters m_cDomainParameters;
    // Qos����
    TQos m_enumQualityOfService;
    // �û�����
    PBYTEArray m_cUserData;
};


/*====================================================================
���� �� CConferenceInviteResponse
���� �� ��������ظ�ԭ��
====================================================================*/
class CConferenceInviteResponse : public CMsg
{
public:
    CConferenceInviteResponse():CMsg(e_Gcc, e_ConferenceInviteResponse)
    {
    }

    // ������
    u32 m_nInviteTag;
    // ����ID
    u32 m_nConferenceID;
    // ��������
    PString m_strConferenceName;
    // �����������η�
    PString m_strConferenceNameModifier;
    // �û��������������������ƣ�
    u32 m_nFlowControl;
    // �����Ӧ��Mcs����
    TDomainParameters m_cDomainParameters;
    // Qos����
    TQos m_enumQualityOfService;
    // �û�����
    PBYTEArray m_cUserData;
    // �������
    ConferenceResponseResult m_enumResult;
};


/*====================================================================
���� �� CConferenceInviteConfirm
���� �� ��������ȷ��ԭ��
====================================================================*/
class CConferenceInviteConfirm : public CMsg
{
public:
    CConferenceInviteConfirm():CMsg(e_Gcc, e_ConferenceInviteConfirm)
    {
    }

    // ����ID
    u32 m_nConferenceID;
    // ����ڵ��ַ
    PString m_strTargetAddr;
    // �û�����
    PBYTEArray m_cUserData;
    // �������
    ConferenceResponseResult m_enumResult;
};


/*====================================================================
���� �� CConferenceDisconnectRequest
���� �� ����Ͽ�����ԭ��
====================================================================*/
class CConferenceDisconnectRequest : public CMsg
{
public:
    CConferenceDisconnectRequest():CMsg(e_Gcc, e_ConferenceDisconnectRequest)
    {
    }

    // ����ID
    u32 m_nConferenceID;
    // GccConference�Ķ�����Դ
    TMessageContext m_tGccConference;
};


/*====================================================================
���� �� CConferenceDisconnectIndication
���� �� ����Ͽ�ָʾԭ��
====================================================================*/
class CConferenceDisconnectIndication : public CMsg
{
public:
    CConferenceDisconnectIndication():CMsg(e_Gcc, e_ConferenceDisconnectIndication)
    {
    }

    // ����ID
    u32 m_nConferenceID;
    // �Ͽ��ڵ��NodeID
    TUserId m_nDisconnectingNodeID;
};


/*====================================================================
���� �� CConferenceDisconnectConfirm
���� �� ����Ͽ�ȷ��ԭ��
====================================================================*/
class CConferenceDisconnectConfirm : public CMsg
{
public:
    CConferenceDisconnectConfirm():CMsg(e_Gcc, e_ConferenceDisconnectConfirm)
    {
    }

    // ����ID
    u32 m_nConferenceID;
    // GccConference�Ķ�����Դ
    TMessageContext m_tGccConference;
    // �������
    ConferenceResponseResult m_enumResult;
};


/*====================================================================
���� �� CConferenceTerminateRequest
���� �� ������������ԭ��
====================================================================*/
class CConferenceTerminateRequest : public CMsg
{
public:
    CConferenceTerminateRequest():CMsg(e_Gcc, e_ConferenceTerminateRequest)
    {
    }

    // ����ID
    u32 m_nConferenceID;
    // ����ԭ��
    ConferenceTerminateReason m_enumReason;
};


/*====================================================================
���� �� CConferenceTerminateIndication
���� �� ��������ָʾԭ��
====================================================================*/
class CConferenceTerminateIndication : public CMsg
{
public:
    CConferenceTerminateIndication():CMsg(e_Gcc, e_ConferenceTerminateIndication)
    {
    }

    // ����ID
    u32 m_nConferenceID;
    // ����ԭ��
    ConferenceTerminateReason m_enumReason;
};


/*====================================================================
���� �� CConferenceTerminateConfirm
���� �� ��������ȷ��ԭ��
====================================================================*/
class CConferenceTerminateConfirm : public CMsg
{
public:
    CConferenceTerminateConfirm():CMsg(e_Gcc, e_ConferenceTerminateConfirm)
    {
    }

    // ����ID
    u32 m_nConferenceID;
    // �������
    ConferenceResponseResult m_enumResult;
};


/*====================================================================
���� �� CConferenceEjectUserRequest
���� �� �ҶϽڵ�����ԭ��
====================================================================*/
class CConferenceEjectUserRequest : public CMsg
{
public:
    CConferenceEjectUserRequest():CMsg(e_Gcc, e_ConferenceEjectUserRequest)
    {
    }

    // ����ID
    u32 m_nConferenceID;
    // ���ҶϽڵ��NodeID
    TUserId m_nEjectedNodeID;
    // �Ҷ�ԭ��
    EjectUserReason m_enumReason;
};


/*====================================================================
���� �� CConferenceEjectUserIndication
���� �� �ҶϽڵ�ָʾԭ��
====================================================================*/
class CConferenceEjectUserIndication : public CMsg
{
public:
    CConferenceEjectUserIndication():CMsg(e_Gcc, e_ConferenceEjectUserIndication)
    {
    }

    // ����ID
    u32 m_nConferenceID;
    // ���ҶϽڵ��NodeID
    TUserId m_nEjectedNodeID;
    // �Ҷ�ԭ��
    EjectUserReason m_enumReason;
};


/*====================================================================
���� �� CConferenceEjectUserConfirm
���� �� �ҶϽڵ�ȷ��ԭ��
====================================================================*/
class CConferenceEjectUserConfirm : public CMsg
{
public:
    CConferenceEjectUserConfirm():CMsg(e_Gcc, e_ConferenceEjectUserConfirm)
    {
    }

    // ����ID
    u32 m_nConferenceID;
    // ���ҶϽڵ��NodeID
    TUserId m_nEjectedNodeID;
    // �������
    EjectUserResult m_enumResult;
};


/*====================================================================
���� �� CConferenceAnnouncePresenceRequest
���� �� �����ڵ�����ԭ��
====================================================================*/
class CConferenceAnnouncePresenceRequest : public CMsg
{
public:
    CConferenceAnnouncePresenceRequest():CMsg(e_Gcc, e_ConferenceAnnouncePresenceRequest)
    {
    }

    // ����ID
    u32 m_nConferenceID;
    // �ڵ�����
    NodeType m_enumNodeType;
    // �ڵ�����
    NodeCategory m_enumNodeCategory;
    // �ڵ�����
    PString m_strNodeName;
    // �û�����
    PBYTEArray m_cUserData;
};


/*====================================================================
���� �� CConferenceAnnouncePresenceConfirm
���� �� �����ڵ�ȷ��ԭ��
====================================================================*/
class CConferenceAnnouncePresenceConfirm : public CMsg
{
public:
    CConferenceAnnouncePresenceConfirm():CMsg(e_Gcc, e_ConferenceAnnouncePresenceConfirm)
    {
    }

    // ����ID
    u32 m_nConferenceID;
    // �������
    ConferenceResponseResult m_enumResult;
};


/*====================================================================
���� �� CConferenceRosterReportIndication��δʹ�ã�
���� �� ����ǼǱ�㱨ָʾԭ��
====================================================================*/
class CConferenceRosterReportIndication : public CMsg
{
public:
    CConferenceRosterReportIndication():CMsg(e_Gcc, e_ConferenceRosterReportIndication)
    {
    }

    // ����ID
    u32 m_nConferenceID;
    // ����ǼǱ�
//    CConferenceRoster m_cConferenceRoster;
};


/*====================================================================
���� �� CConferenceNodeAddIndication
���� �� �����������ڵ�֪ͨԭ��
====================================================================*/
class CConferenceNodeAddIndication : public CMsg
{
public:
    CConferenceNodeAddIndication():CMsg(e_Gcc, e_ConferenceNodeAddIndication)
    {
    }

    // �ýڵ��NodeId
    TUserId m_nNodeId;
    // �ýڵ���ϼ��ڵ�NodeId
    TUserId m_nAboveNodeId;
    // �ýڵ����Դ
    PString m_strFrom;
    // �ýڵ������(λ��)
    ConfNodePos m_enumNodePos;
    // �ýڵ������(MCU/MT)
    NodeType m_enumNodeType;
    // �Ƿ񱻶����յ�����
    bool m_bIsPassive;
    // �ýڵ������
    PString m_strNodeName;
    // �ýڵ��Email
    PString m_strNodeEmail;
    // �ýڵ�ĵ绰
    PString m_strNodePhone;
    // �ýڵ�ĵ�ַ
    PString m_strNodeLoc;
    // �û�����
    void*   m_pUserData;
};


/*====================================================================
���� �� CConferenceNodeAddIndication
���� �� �����������ڵ�֪ͨԭ��
====================================================================*/
class CConferenceNodeRemoveIndication : public CMsg
{
public:
    CConferenceNodeRemoveIndication():CMsg(e_Gcc, e_ConferenceNodeRemoveIndication)
    {
    }

    // �ýڵ��NodeId
    TUserId m_nRemovedNodeId;
};




/*====================================================================
���� �� CConferenceApeMaskIndication
���� �� ָ��Ӧ������֪ͨԭ��
====================================================================*/
class CConferenceApeMaskIndication : public CMsg
{
public:
    CConferenceApeMaskIndication():CMsg(e_Gcc, e_ConferenceApeMaskIndication)
    {
    }

    // Ӧ������
    u8 m_nApeMask;
};


/*====================================================================
���� �� CConferenceRosterInquireRequest
���� �� ����ǼǱ��ѯ����ԭ��
====================================================================*/
class CConferenceRosterInquireRequest : public CMsg
{
public:
    CConferenceRosterInquireRequest():CMsg(e_Gcc, e_ConferenceRosterInquireRequest)
    {
    }

    // ����ID
    u32 m_nConferenceID;
};


/*====================================================================
���� �� CConferenceRosterInquireConfirm
���� �� ����ǼǱ��ѯȷ��ԭ�δʹ�ã�
====================================================================*/
class CConferenceRosterInquireConfirm : public CMsg
{
public:
    CConferenceRosterInquireConfirm():CMsg(e_Gcc, e_ConferenceRosterInquireConfirm)
    {
    }

    // ����ID
    u32 m_nConferenceID;
    // ��������
    PString m_strConferenceName;
    // ��������
    PString m_strConferenceDescription;
    // ����ǼǱ�
//    CConferenceRoster m_cConferenceRoster;
    // �������
    ConferenceResponseResult m_enumResult;
};


/*====================================================================
���� �� CApplicationPermissionToEnrollIndication
���� �� ����Ӧ�õǼ�ָʾԭ��
====================================================================*/
class CApplicationPermissionToEnrollIndication : public CMsg
{
public:
    CApplicationPermissionToEnrollIndication():CMsg(e_Gcc, e_ApplicationPermissionToEnrollIndication)
    {
    }

    // ����ID
    u32 m_nConferenceID;
    // ����Grant��������Revoke��
    EnrollPermission m_enumFlag;
};


/*====================================================================
���� �� CApplicationEnrollRequest
���� �� Ӧ�õǼ�����ԭ��
====================================================================*/
class CApplicationEnrollRequest : public CMsg
{
public:
    CApplicationEnrollRequest():CMsg(e_Gcc, e_ApplicationEnrollRequest)
    {
    }

    // ����ID
    u32 m_nConferenceID;
    // �Ự��Session��ID
    SessionKey m_cSessionKey;
    // Active��־
    bool m_bActiveFlag;
    // ��APE��ApeID
    TUserId m_nApplicationUserID;
    // �Ƿ�Ǽǣ�true���Ǽǣ�false�����Ǽǣ�
    bool m_bEnrollFlag;
    // Ape����Ϣ
    ApplicationRecord m_cAppRecord;
    // ��������Ϣ
    TApeCapabilitiesList m_listApeCapabilities;
};


/*====================================================================
���� �� CApplicationEnrollConfirm
���� �� Ӧ�õǼ�ȷ��ԭ��
====================================================================*/
class CApplicationEnrollConfirm : public CMsg
{
public:
    CApplicationEnrollConfirm():CMsg(e_Gcc, e_ApplicationEnrollConfirm)
    {
    }

    // ����ID
    u32 m_nConferenceID;
    // �Ự��Session��ID
    SessionKey m_cSessionKey;
    // ��APE��ApeID
    TApeId m_nApeId;
    // APE���ڽڵ��NodeID
    TUserId m_nNodeID;
    // �������
    ConferenceResponseResult m_enumResult;
};


/*====================================================================
���� �� CApplicationRosterReportIndication
���� �� Ӧ�õǼǱ�㱨ָʾԭ�δʹ�ã�
====================================================================*/
class CApplicationRosterReportIndication : public CMsg
{
public:
    CApplicationRosterReportIndication():CMsg(e_Gcc, e_ApplicationRosterReportIndication)
    {
    }

    // ����ID
    u32 m_nConferenceID;
    // Ӧ�õǼǱ�ĸ��²���
//    CUpdatedApplicationRoster m_cUpdatedApplicationRoster;
};



/*====================================================================
���� �� CConferenceApeAddIndication
���� �� ����������Ӧ��֪ͨԭ��
====================================================================*/
class CConferenceApeAddIndication : public CMsg
{
public:
    CConferenceApeAddIndication():CMsg(e_Gcc, e_ConferenceApeAddIndication)
    {
    }

    // ����ID
    u32 m_nConferenceId;
    // ��Ape��SProtocolKey
    Key m_cProtocolKey;
    // ��Ape���ڵĽڵ�NodeId
    TUserId m_nNodeId;
    // ��Ape�ڸýڵ��ϵ�Entity���
    u32 m_nEntityId;
    // ��Ape����Ϣ
    ApplicationRecord m_cApeRec;
    // �����Ape���ܼ���
    u32 m_nParticipantsNum;
};


/*====================================================================
���� �� CConferenceApeReplaceIndication
���� �� �������޸�Ӧ��֪ͨԭ��
====================================================================*/
class CConferenceApeReplaceIndication : public CMsg
{
public:
    CConferenceApeReplaceIndication():CMsg(e_Gcc, e_ConferenceApeReplaceIndication)
    {
    }

    // ����ID
    u32 m_nConferenceId;
    // ��Ape��SProtocolKey
    Key m_cProtocolKey;
    // ��Ape���ڵĽڵ�NodeId
    TUserId m_nNodeId;
    // ��Ape�ڸýڵ��ϵ�Entity���
    u32 m_nEntityId;
    // ��Ape����Ϣ
    ApplicationRecord m_cApeRec;
    // �����Ape���ܼ���
    u32 m_nParticipantsNum;
};




/*====================================================================
���� �� CConferenceApeRemoveIndication
���� �� ����������Ӧ��֪ͨԭ��
====================================================================*/
class CConferenceApeRemoveIndication : public CMsg
{
public:
    CConferenceApeRemoveIndication():CMsg(e_Gcc, e_ConferenceApeRemoveIndication)
    {
    }
    
    Key m_cProtocolKey;
    // ��Ape���ڵĽڵ�NodeId
    TUserId m_nNodeId;
    // ��Ape�ڸýڵ��ϵ�Entity���
    u32 m_nEntityId;
    // �����Ape���ܼ���
    u32 m_nParticipantsNum;
};



/*====================================================================
���� �� CApplicationRosterInquireRequest
���� �� Ӧ�õǼǱ��ѯ����ԭ��
====================================================================*/
class CApplicationRosterInquireRequest : public CMsg
{
public:
    CApplicationRosterInquireRequest():CMsg(e_Gcc, e_ApplicationRosterInquireRequest)
    {
    }

    // ����ID
    u32 m_nConferenceID;
    // �Ự��Session��ID
    SessionKey m_cSessionKey;
    // ��ѯ�μӸ�Ape��ʵ������
    bool m_bQuireSum;
    // ��ѯ���и�Ape��������
    bool m_bQuireCap;
};


/*====================================================================
���� �� CApplicationRosterInquireConfirm
���� �� Ӧ�õǼǱ��ѯȷ��ԭ��
====================================================================*/
class CApplicationRosterInquireConfirm : public CMsg
{
public:
    CApplicationRosterInquireConfirm():CMsg(e_Gcc, e_ApplicationRosterInquireConfirm)
    {
    }

    // ����ID
    u32 m_nConferenceID;
    // �Ự��Session��ID
    SessionKey m_cSessionKey;
    // Ӧ�õǼǱ�<Key:�ڵ�Id����������Ϣ>
    std::map<TUserId, ApplicationRecord> m_mapNodeCap;
    // �μӸ�Ӧ�õĽڵ����
    s32 m_nApeCount;
    // �������
    ConferenceResponseResult m_enumResult;
};


/*====================================================================
���� �� CRegistryRegisterChannelRequest
���� �� ע���ŵ�����ԭ��
====================================================================*/
class CRegistryRegisterChannelRequest : public CMsg
{
public:
    CRegistryRegisterChannelRequest():CMsg(e_Gcc, e_RegistryRegisterChannelRequest)
    {
    }

    // ����ID
    u32 m_nConferenceID;
    // SessionKey
    SessionKey m_cSessionKey;
    // ע��Key
    PBYTEArray m_strRegistryKey;
    // ע��value���ŵ�ID
    TChannelId m_nChannelID;
};


/*====================================================================
���� �� CRegistryRegisterChannelConfirm
���� �� ע���ŵ�ȷ��ԭ��
====================================================================*/
class CRegistryRegisterChannelConfirm : public CMsg
{
public:
    CRegistryRegisterChannelConfirm():CMsg(e_Gcc, e_RegistryRegisterChannelConfirm)
    {
    }

    // ע����
    RegistryResponse m_cRegistryResponse;
};


/*====================================================================
���� �� CRegistryAssignTokenRequest
���� �� ����ע����������ԭ��
====================================================================*/
class CRegistryAssignTokenRequest : public CMsg
{
public:
    CRegistryAssignTokenRequest():CMsg(e_Gcc, e_RegistryAssignTokenRequest)
    {
    }

    // ����ID
    u32 m_nConferenceID;
    // ���벢��ȡ���û�ID
    TUserId m_nRequestUserId;
    // SessionKey
    SessionKey m_cSessionKey;
    // ע��Key
    PBYTEArray m_strRegistryKey;
};


/*====================================================================
���� �� CRegistryAssignTokenConfirm
���� �� ����ע������ȷ��ԭ��
====================================================================*/
class CRegistryAssignTokenConfirm : public CMsg
{
public:
    CRegistryAssignTokenConfirm():CMsg(e_Gcc, e_RegistryAssignTokenConfirm)
    {
    }

    // ע����
    RegistryResponse m_cRegistryResponse;
};


/*====================================================================
���� �� CRegistryRetrieveEntryRequest
���� �� ��ѯע��������ԭ��
====================================================================*/
class CRegistryRetrieveEntryRequest : public CMsg
{
public:
    CRegistryRetrieveEntryRequest():CMsg(e_Gcc, e_RegistryRetrieveEntryRequest)
    {
    }

    // ����ID
    u32 m_nConferenceID;
    // ע��Key
    PBYTEArray m_strRegistryKey;
};


/*====================================================================
���� �� CRegistryRetrieveEntryConfirm
���� �� ��ѯע����ȷ��ԭ��
====================================================================*/
class CRegistryRetrieveEntryConfirm : public CMsg
{
public:
    CRegistryRetrieveEntryConfirm():CMsg(e_Gcc, e_RegistryRetrieveEntryConfirm)
    {
    }

    // ע����
    RegistryResponse m_cRegistryResponse;
};


/*====================================================================
���� �� CRegistryDeleteEntryRequest
���� �� ɾ��ע��������ԭ��
====================================================================*/
class CRegistryDeleteEntryRequest : public CMsg
{
public:
    CRegistryDeleteEntryRequest():CMsg(e_Gcc, e_RegistryDeleteEntryRequest)
    {
    }

    // ����ID
    u32 m_nConferenceID;
    // ע��Key
    PBYTEArray m_strRegistryKey;
};


/*====================================================================
���� �� CRegistryDeleteEntryConfirm
���� �� ɾ��ע����ȷ��ԭ��
====================================================================*/
class CRegistryDeleteEntryConfirm : public CMsg
{
public:
    CRegistryDeleteEntryConfirm():CMsg(e_Gcc, e_RegistryDeleteEntryConfirm)
    {
    }

    // ע����
    RegistryResponse m_cRegistryResponse;
};


/*====================================================================
���� �� CRegistryAllocateHandleRequest
���� �� ����������ԭ��
====================================================================*/
class CRegistryAllocateHandleRequest : public CMsg
{
public:
    CRegistryAllocateHandleRequest():CMsg(e_Gcc, e_RegistryAllocateHandleRequest)
    {
    }

    // ����ID
    u32 m_nConferenceID;
    // SessionKey
    SessionKey m_cSessionKey;
    // ����������Ŀ
    u32 m_nNumberOfHandles;
};


/*====================================================================
���� �� CRegistryAllocateHandleConfirm
���� �� ������ȷ��ԭ��
====================================================================*/
class CRegistryAllocateHandleConfirm : public CMsg
{
public:
    CRegistryAllocateHandleConfirm():CMsg(e_Gcc, e_RegistryAllocateHandleConfirm)
    {
    }

    // ������
    RegistryAllocateHandleResponse m_cAllocateResposne;
};


/*====================================================================
���� �� CAssignConductorRequest
���� �� ������ϯ����ԭ��
====================================================================*/
class CAssignConductorRequest : public CMsg
{
public:
    CAssignConductorRequest():CMsg(e_Gcc, e_AssignConductorRequest)
    {
    }

    // ��ϯ�������ַ
    PString m_strConductorAddr;
    // ��ϯ��Ӧ������
    BYTE m_byteConductorApeMask;
    // ����ϯ��Ӧ������
    BYTE m_byteNormalApeMask;
};


/*====================================================================
���� �� CGccSetFlowControl
���� �� �������ƴ�������
====================================================================*/
class CGccSetFlowControl : public CMsg
{
public:
    CGccSetFlowControl():CMsg(e_Gcc, e_ConfSetFlowControl)
    {
    }

    // ���õ�����������λ Byte/s
    s32 m_nFlowBand;
};


/*====================================================================
���� �� CGccFlowControlConfirm
���� �� �������ƴ������ý��
====================================================================*/
class CGccFlowControlConfirm : public CMsg
{
public:
    CGccFlowControlConfirm():CMsg(e_Gcc, e_ConfFlowControlConfirm)
    {
    }

    // �����õ�����������λ Byte/s
    s32 m_nFlowBand;
};


#endif
