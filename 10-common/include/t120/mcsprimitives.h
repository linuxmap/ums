/******************************************************************************
ģ����      ��McsPrimitives
�ļ���      ��McsPrimitives.h
����ļ�    ��McsPrimitives.cpp
�ļ�ʵ�ֹ��ܣ���������MCSԭ��
����        ������
�汾        ��4.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �߶���      �޸�����
24/05/05    4.0         ����        ����        ����
******************************************************************************/
#ifndef _MCS_PRIMITIVES_H_
#define _MCS_PRIMITIVES_H_

#include <mqm.h>
#include <mcstypes.h>

// �������ƶ��壺��λ Byte/s
#define  NO_FLOW_CONTROL        -1
#define  MIN_FLOW_MIN_VALUE     64*1024


// Mcs��Ϣ����(С)����
typedef enum
{
    // ��GccProvider��McsProvider
    e_Bind                          = 0,
    // ��ʼ�������ݼ������
    e_StartRequest                  = 1, 
    // �������ݼ��ظ�
    e_StartConfirm                  = 2,
    // ���ӽڵ�����ԭ��
    e_ConnectProviderRequest        = 3, 
    // ���ӽڵ�ָʾԭ��
    e_ConnectProviderIndication     = 4,
    // ���ӽڵ�ظ�ԭ��
    e_ConnectProviderResponse       = 5,
    // ���ӽڵ�ȷ��ԭ��
    e_ConnectProviderConfirm        = 6,
    // �Ͽ��ڵ�����ԭ��
    e_DisconnectProviderRequest     = 7, 
    // �Ͽ��ڵ�ָʾԭ��
    e_DisconnectProviderIndication  = 8, 
    //����Domainԭ��
    e_CreateDomainPrimitive         = 49,

    // �����û�����ԭ��
    e_AttachUserRequest             = 9, 
    // �����û�ȷ��ԭ��
    e_AttachUserConfirm             = 10, 
    // ɾ���û�����ԭ��
    e_DetachUserRequest             = 11, 
    // ɾ���û�ָʾԭ��
    e_DetachUserIndication          = 12, 

    // �����ŵ�����ԭ��
    e_ChannelJoinRequest            = 13, 
    // �����ŵ�ȷ��ԭ��
    e_ChannelJoinConfirm            = 14, 
    // �뿪�ŵ�����ԭ��
    e_ChannelLeaveRequest           = 15, 
    // �뿪�ŵ�ָʾԭ��
    e_ChannelLeaveIndication        = 16, 
    // �ټ��ŵ�����ԭ��
    e_ChannelConveneRequest         = 17, 
    // �ټ��ŵ�ȷ��ԭ��
    e_ChannelConveneConfirm         = 18, 
    // ��ɢ�ŵ�����ԭ��
    e_ChannelDisbandRequest         = 19, 
    // ��ɢ�ŵ�ָʾԭ��
    e_ChannelDisbandIndication      = 20, 
    // �����û������ŵ�����ԭ��
    e_ChannelAdmitRequest           = 21,  
    // �����û������ŵ�ָʾԭ��
    e_ChannelAdmitIndication        = 22, 
    // �������û������ŵ�����ԭ��
    e_ChannelExpelRequest           = 23, 
    // �������û������ŵ�ָʾԭ��
    e_ChannelExpelIndication        = 24, 

    // Send��ʽ������������ԭ��
    e_SendDataRequest               = 25, 
    // Send��ʽ��������ָʾԭ��
    e_SendDataIndication            = 26, 
    // UniformSend��ʽ������������ԭ��
    e_UniformSendDataRequest        = 27, 
    // UniformSend��ʽ��������ָʾԭ��
    e_UniformSendDataIndication     = 28, 

    // ���봴����������ԭ��
    e_GenerateTokenRequest          = 29,
    // ���봴������ȷ��ԭ��
    e_GenerateTokenConfirm          = 30,
    // �����������ԭ��
    e_TokenGrabRequest              = 31, 
    // �������ȷ��ԭ��
    e_TokenGrabConfirm              = 32, 
    // ������������ԭ��
    e_TokenInhibitRequest           = 33, 
    // ��������ȷ��ԭ��
    e_TokenInhibitConfirm           = 34, 
    // ������������ԭ��
    e_TokenGiveRequest              = 35, 
    // ��������ָʾԭ��
    e_TokenGiveIndication           = 36, 
    // �������ƻظ�ԭ��
    e_TokenGiveResponse             = 37, 
    // ��������ȷ��ԭ��
    e_TokenGiveConfirm              = 38, 
    // ������������ԭ��
    e_TokenPleaseRequest            = 39, 
    // ��������ָʾԭ��
    e_TokenPleaseIndication         = 40, 
    // �ͷ���������ԭ��
    e_TokenReleaseRequest           = 41, 
    // �ͷ�����ȷ��ԭ��
    e_TokenReleaseConfirm           = 42, 
    // ������������ԭ��
    e_TokenTestRequest              = 43, 
    // ��������ȷ��ԭ��
    e_TokenTestConfirm              = 44,
    // �������ƴ�������
    e_SetFlowControl                = 45,
    // �������ƴ�������
    e_FlowControlConfirm            = 46,
    // �ŵ���ѯ����ԭ��
    e_ChannelQueryRequest           = 47,
    // �ŵ���ѯȷ��ԭ��
    e_ChannelQueryConfirm           = 48
} enumMcsMsgType;


/*====================================================================
���� �� CBindPrimitive
���� �� ���ϲ�Э��Ķ��С���Դ
====================================================================*/
class CMcsBindPrimitive : public CMsg
{
public:
    CMcsBindPrimitive():CMsg(e_Mcs, e_Bind)
    {
    }
};

/*====================================================================
���� �� CMcsStartPrimitive
���� �� MCS��ʼ��������м���
====================================================================*/
class CMcsStartRequest : public CMsg
{
public:
    CMcsStartRequest():CMsg(e_Mcs, e_StartRequest)
    {
    }
    
    // ������ַ
    PString m_strAddress;
};

/*====================================================================
���� �� CMcsStartPrimitive
���� �� MCS��ʼ��������м���
====================================================================*/
class CMcsStartConfirm : public CMsg
{
public:
    CMcsStartConfirm():CMsg(e_Mcs, e_StartConfirm)
    {
    }
    
    // �Ƿ������ɹ�
    bool m_bResult;
};

/*====================================================================
���� �� CMcsConnectProviderRequest
���� �� ���ӽڵ�����ԭ��
====================================================================*/
class CMcsConnectProviderRequest : public CMsg
{
public:
    CMcsConnectProviderRequest():CMsg(e_Mcs, e_ConnectProviderRequest)
    {
    }

    // ���з���ַ
    PString m_strCallingAddress;
    // ���з�Domain��ʶ
    PString m_strCallingDomainSelector;
    // ���з���ַ
    PString m_strCalledAddress;
    // ���з�Domain��ʶ
    PString m_strCalledDomainSelector;
    // ���з����־��ture���ϡ�false����
    bool    m_bUpwardDownwardFlag;
    // Domain����
    TDomainParameters m_cDomainParameters;
    // QoS����
    TQos m_enumQos;
    // �û����ݣ�������Gcc PDU
    PBYTEArray m_cUserData;
};


/*====================================================================
���� �� CMcsConnectProviderIndication
���� �� ���ӽڵ�ָʾԭ��
====================================================================*/
class CMcsConnectProviderIndication : public CMsg
{
public:
    CMcsConnectProviderIndication():CMsg(e_Mcs, e_ConnectProviderIndication)
    {
    }

    // ��Tc��ָ��
    void* m_pTcPointer;
    // ���з���ַ
    PString m_strCallingAddress;
    // ���з�Domain��ʶ
    PString m_strCallingDomainSelector;
    // ���з���ַ
    PString m_strCalledAddress;
    // ���з�Domain��ʶ
    PString m_strCalledDomainSelector;
    // ���з����־��ture���ϡ�false����
    bool    m_bUpwardDownwardFlag;
    // Domain����
    TDomainParameters m_cDomainParameters;
    // QoS����
    TQos m_enumQos;
    // �û����ݣ�������Gcc PDU
    PBYTEArray m_cUserData;
};


/*====================================================================
���� �� CMcsConnectProviderResponse
���� �� ���ӽڵ�ظ�ԭ��
====================================================================*/
class CMcsConnectProviderResponse : public CMsg
{
public:
    CMcsConnectProviderResponse():CMsg(e_Mcs, e_ConnectProviderResponse)
    {
    }

    // ��Tc��ָ��
    void* m_pTcPointer;
    // Domain����
    TDomainParameters m_cDomainParameters;
    // QoS����
    TQos m_enumQos;
    // ���ӽ��
    TResult m_enumResult;
    // ��ӦDOMANIN��MQM��ַ
    TMessageContext m_tMcsDomain;
    // �û����ݣ�������Gcc PDU
	PBYTEArray m_cUserData;
};

/*====================================================================
���� �� CMcsCreateDomainPrimitive
���� �� ��������Զ�˻���ʱ��������Conference��ӦDomainԭ��
====================================================================*/
class CMcsCreateDomainPrimitive: public CMsg
{
public:
    CMcsCreateDomainPrimitive():CMsg(e_Mcs, e_CreateDomainPrimitive)
    {
    }   
    //��Ҫ����Է������ĵ�ַ
    PString m_strAddress;
};

/*====================================================================
���� �� CMcsConnectProviderConfirm
���� �� ���ӽڵ�ȷ��ԭ��
====================================================================*/
class CMcsConnectProviderConfirm : public CMsg
{
public:
    CMcsConnectProviderConfirm():CMsg(e_Mcs, e_ConnectProviderConfirm)
    {
    }

    // ���з���ַ
    PString m_strCalledAddress;
    // Domain����
    TDomainParameters m_cDomainParameters;
    // QoS����
    TQos m_enumQos;
    // ���ӽ��
    TResult m_enumResult;
    // �û����ݣ�������Gcc PDU
	PBYTEArray m_cUserData;
};


/*====================================================================
���� �� CMcsDisconnectProviderRequest
���� �� �Ͽ��ڵ�����ԭ��
====================================================================*/
class CMcsDisconnectProviderRequest : public CMsg
{
public:
    CMcsDisconnectProviderRequest():CMsg(e_Mcs, e_DisconnectProviderRequest)
    {
    }
    
    // ����Disconnect��Domain
    TMessageContext m_tMcsDomain;
};


/*====================================================================
���� �� CMcsDisconnectProviderIndication
���� �� �Ͽ��ڵ�ָʾԭ��
====================================================================*/
class CMcsDisconnectProviderIndication : public CMsg
{
public:
    CMcsDisconnectProviderIndication():CMsg(e_Mcs, e_DisconnectProviderIndication)
    {
    }

    // �Ͽ����ӵ�ԭ��
    TReason m_enumReason;
    // �Ƿ����ϼ��ڵ�Ͽ�
    bool m_bAboveDisconnect;
};


/*====================================================================
���� �� CMcsAttachUserRequest
���� �� �����û�����ԭ��
====================================================================*/
class CMcsAttachUserRequest : public CMsg
{
public:
    CMcsAttachUserRequest():CMsg(e_Mcs, e_AttachUserRequest)
    {
    }

    // Domain��ʶ
    PString m_strDomainSelector;
};


/*====================================================================
���� �� CMcsAttachUserConfirm
���� �� �����û�ȷ��ԭ��
====================================================================*/
class CMcsAttachUserConfirm : public CMsg
{
public:
    CMcsAttachUserConfirm():CMsg(e_Mcs, e_AttachUserConfirm)
    {
    }

    // ������
    TResult  m_enumResult;
    // �õ����û�ID
    TUserId m_nUserId;
};


/*====================================================================
���� �� CMcsDetachUserRequest
���� �� ɾ���û�����ԭ��
====================================================================*/
class CMcsDetachUserRequest : public CMsg
{
public:
    CMcsDetachUserRequest():CMsg(e_Mcs, e_DetachUserRequest)
    {
    }

public:
    // ɾ�����û�ID�б�
    TUserIdList m_listUserIds;
};


/*====================================================================
���� �� CMcsDetachUserIndication
���� �� ɾ���û�ָʾԭ��
====================================================================*/
class CMcsDetachUserIndication : public CMsg
{
public:
    CMcsDetachUserIndication():CMsg(e_Mcs, e_DetachUserIndication)
    {
    }

    // ɾ�����
    TResult  m_enumResult;
    // ɾ�����û�ID�б�
    TUserIdList m_listUserIds;
};


/*====================================================================
���� �� CMcsChannelJoinRequest
���� �� �����ŵ�����ԭ��
====================================================================*/
class CMcsChannelJoinRequest : public CMsg
{
public:
    CMcsChannelJoinRequest():CMsg(e_Mcs, e_ChannelJoinRequest)
    {
    }

    TUserId m_nUserId;
    // ���������ŵ�ID
    TChannelId m_nChannelToJoin;
};


/*====================================================================
���� �� CMcsChannelJoinConfirm
���� �� �����ŵ�ȷ��ԭ��
====================================================================*/
class CMcsChannelJoinConfirm : public CMsg
{
public:
    CMcsChannelJoinConfirm():CMsg(e_Mcs, e_ChannelJoinConfirm)
    {
    }

    // �����û�
    TUserId m_nUserId;
    // ���������ŵ�ID
    TChannelId m_nChannelToJoin;
    // ������ŵ�ID
    TChannelId m_nChannelJoined;
    // ������
    TResult     m_enumResult;
};


/*====================================================================
���� �� CMcsChannelLeaveRequest
���� �� �뿪�ŵ�����ԭ��
====================================================================*/
class CMcsChannelLeaveRequest : public CMsg
{
public:
    CMcsChannelLeaveRequest():CMsg(e_Mcs, e_ChannelLeaveRequest)
    {
    }

    // �����뿪���û�
    TUserId m_nUserId;
    // �����뿪���ŵ�ID
    TChannelId m_nChannelToLeave;
};


/*====================================================================
���� �� CMcsChannelLeaveIndication
���� �� �뿪�ŵ�ָʾԭ��
====================================================================*/
class CMcsChannelLeaveIndication : public CMsg
{
public:
    CMcsChannelLeaveIndication():CMsg(e_Mcs, e_ChannelLeaveIndication)
    {
    }

    // �����뿪���ŵ�ID
    TChannelId m_nChannelToLeave;
    // ������
    TResult     m_enumResult;
};


/*====================================================================
���� �� CMcsChannelConveneRequest
���� �� �ټ��ŵ�����ԭ��
====================================================================*/
class CMcsChannelConveneRequest : public CMsg
{
public:
    CMcsChannelConveneRequest():CMsg(e_Mcs, e_ChannelConveneRequest)
    {
    }
    // �ټ���
    TUserId m_nUserId;
};


/*====================================================================
���� �� CMcsChannelConveneConfirm
���� �� �ټ��ŵ�ȷ��ԭ��
====================================================================*/
class CMcsChannelConveneConfirm : public CMsg
{
public:
    CMcsChannelConveneConfirm():CMsg(e_Mcs, e_ChannelConveneConfirm)
    {
    }

    // ������
    TResult     m_enumResult;
    // �ټ����ŵ�
    TChannelId m_nConvenedChannelId;
};


/*====================================================================
���� �� CMcsChannelDisbandRequest
���� �� ��ɢ�ŵ�����ԭ��
====================================================================*/
class CMcsChannelDisbandRequest : public CMsg
{
public:
    CMcsChannelDisbandRequest():CMsg(e_Mcs, e_ChannelDisbandRequest)
    {
    }

    // �����ɢ���ŵ�
    TChannelId m_nChannelToDisband;
    // �����ɢ���û�
    TUserId m_nUserId;
};


/*====================================================================
���� �� CMcsChannelDisbandIndication
���� �� ��ɢ�ŵ�ָʾԭ��
====================================================================*/
class CMcsChannelDisbandIndication : public CMsg
{
public:
    CMcsChannelDisbandIndication():CMsg(e_Mcs, e_ChannelDisbandIndication)
    {
    }

    // ����ɢ���ŵ�
    TChannelId m_nChannelToDisband;
    // ��ɢ���
    TResult     m_enumResult;
};


/*====================================================================
���� �� CMcsChannelAdmitRequest
���� �� �����û������ŵ�����ԭ��
====================================================================*/
class CMcsChannelAdmitRequest : public CMsg
{
public:
    CMcsChannelAdmitRequest():CMsg(e_Mcs, e_ChannelAdmitRequest)
    {
    }

    // ˽���ŵ�ID
    TChannelId     m_nChannelToAdmit;
    // ���������ŵ����û��б�
    TUserIdList m_listAdmitedUserIds;
    // ���������û�
    TUserId m_nUserId;
};


/*====================================================================
���� �� CMcsChannelAdmitIndication
���� �� �����û������ŵ�ָʾԭ��
====================================================================*/
class CMcsChannelAdmitIndication : public CMsg
{
public:
    CMcsChannelAdmitIndication():CMsg(e_Mcs, e_ChannelAdmitIndication)
    {
    }

    // ˽���ŵ�ID
    TChannelId m_nChannelToAdmit;
    // ��˽���ŵ��Ĺ�����
    TUserId    m_nManagerUserId;
};


/*====================================================================
���� �� CMcsChannelExpelRequest
���� �� �������û������ŵ�����ԭ��
====================================================================*/
class CMcsChannelExpelRequest : public CMsg
{
public:
    CMcsChannelExpelRequest():CMsg(e_Mcs, e_ChannelExpelRequest)
    {
    }

    // ˽���ŵ�ID
    TChannelId         m_nChannelToExpel;
    // �����������ŵ����û��б�
    TUserIdList m_listExpeledUserIds;
    // �����߳����û�
    TUserId m_nUserId;
};


/*====================================================================
���� �� CMcsChannelExpelIndication
���� �� �������û������ŵ�ָʾԭ��
====================================================================*/
class CMcsChannelExpelIndication : public CMsg
{
public:
    CMcsChannelExpelIndication():CMsg(e_Mcs, e_ChannelExpelIndication)
    {
    }

    // ˽���ŵ�ID
    TChannelId m_nChannelToExpel;
    // ���ܾ���ԭ��
    TReason     m_enumReason;
};


/*====================================================================
���� �� CSendDataRequest
���� �� Send��ʽ������������ԭ��
====================================================================*/
class CSendDataRequest : public CMsg
{
public:
    CSendDataRequest():CMsg(e_Mcs, e_SendDataRequest)
    {
    }

    // �������ȼ�
    TDataPriority   m_enumPriroty;
    // �������ݵ����ŵ�
    TChannelId m_nChannelId;
    // �����ݵķ�����
    TUserId    m_nSenderId;
    // Ҫ���͵�����
    PBYTEArray m_cData;
};


/*====================================================================
���� �� CSendDataIndication
���� �� Send��ʽ��������ָʾԭ��
====================================================================*/
class CSendDataIndication : public CMsg
{
public:
    CSendDataIndication():CMsg(e_Mcs, e_SendDataIndication)
    {
    }

    // �������ȼ�
    TDataPriority   m_enumPriroty;
    // ���ݴӸ��ŵ��õ�
    TChannelId m_nChannelId;
    // �����ݵķ�����
    TUserId    m_nSenderId;
    // ���յ�������
    PBYTEArray m_cData;
};


/*====================================================================
���� �� CUniformSendDataRequest
���� �� UniformSend��ʽ������������ԭ��
====================================================================*/
class CUniformSendDataRequest : public CMsg
{
public:
    CUniformSendDataRequest():CMsg(e_Mcs, e_UniformSendDataRequest)
    {
    }

    // �������ȼ�
    TDataPriority   m_enumPriroty;
    // �������ݵ����ŵ�
    TChannelId m_nChannelId;
    // ���ݵķ�����
    TUserId m_nSenderId;
    // Ҫ���͵�����
    PBYTEArray m_cData;
};


/*====================================================================
���� �� CUniformSendDataIndication
���� �� UniformSend��ʽ��������ָʾԭ��
====================================================================*/
class CUniformSendDataIndication : public CMsg
{
public:
    CUniformSendDataIndication():CMsg(e_Mcs, e_UniformSendDataIndication)
    {
    }

    // �������ȼ�
    TDataPriority   m_enumPriroty;
    // ���ݴӸ��ŵ��õ�
    TChannelId m_nChannelId;
    // �����ݵķ�����
    TUserId    m_nSenderId;
    // ���յ�������
    PBYTEArray m_cData;
};



/*====================================================================
���� �� CMcsGenerateTokenIdRequest
���� �� ������������ԭ��
====================================================================*/
class CMcsGenerateTokenRequest : public CMsg
{
public:
    CMcsGenerateTokenRequest():CMsg(e_Mcs, e_GenerateTokenRequest)
    {
    }

};



/*====================================================================
���� �� CMcsGenerateTokenIdConfirm
���� �� ��������ȷ��ԭ��
====================================================================*/
class CMcsGenerateTokenConfirm : public CMsg
{
public:
    CMcsGenerateTokenConfirm():CMsg(e_Mcs, e_GenerateTokenConfirm)
    {
    }

    // ����������ID
    TTokenId m_nTokenId;
};


/*====================================================================
���� �� CMcsTokenGrabRequest
���� �� �����������ԭ��
====================================================================*/
class CMcsTokenGrabRequest : public CMsg
{
public:
    CMcsTokenGrabRequest():CMsg(e_Mcs, e_TokenGrabRequest)
    {
    }

    // �����ȡ������ID
    TTokenId m_nTokenId;
    // ������
    TUserId m_nGrabberId;
};


/*====================================================================
���� �� CMcsTokenGrabConfirm
���� �� �������ȷ��ԭ��
====================================================================*/
class CMcsTokenGrabConfirm : public CMsg
{
public:
    CMcsTokenGrabConfirm():CMsg(e_Mcs, e_TokenGrabConfirm)
    {
    }

    // �����ȡ������ID
    TTokenId m_nTokenId;
    // ������
    TResult m_enumResult;
    // ����״̬
    TTokenStatus m_enumStatus;
};


/*====================================================================
���� �� CMcsTokenInhibitRequest
���� �� ������������ԭ��
====================================================================*/
class CMcsTokenInhibitRequest : public CMsg
{
public:
    CMcsTokenInhibitRequest():CMsg(e_Mcs, e_TokenInhibitRequest)
    {
    }

    // �������Ƶ�����ID
    TTokenId m_nTokenId;
    // ������ID
    TUserId m_nInitiator;
};


/*====================================================================
���� �� CMcsTokenInhibitConfirm
���� �� ��������ȷ��ԭ��
====================================================================*/
class CMcsTokenInhibitConfirm : public CMsg
{
public:
    CMcsTokenInhibitConfirm():CMsg(e_Mcs, e_TokenInhibitConfirm)
    {
    }

    // �������Ƶ�����ID
    TUserId m_nTokenId;
    // ������
    TResult m_enumResult;
    // ����״̬
    TTokenStatus m_enumStatus;
};


/*====================================================================
���� �� CMcsTokenGiveRequest
���� �� ������������ԭ��
====================================================================*/
class CMcsTokenGiveRequest : public CMsg
{
public:
    CMcsTokenGiveRequest():CMsg(e_Mcs, e_TokenGiveRequest)
    {
    }

    // ���ƵĽ�����ID
    TUserId  m_nRecverId;
    // ���󴫵ݵ�����ID
    TTokenId m_nTokenId;
};


/*====================================================================
���� �� CMcsTokenGiveIndication
���� �� ��������ָʾԭ��
====================================================================*/
class CMcsTokenGiveIndication : public CMsg
{
public:
    CMcsTokenGiveIndication():CMsg(e_Mcs, e_TokenGiveIndication)
    {
    }

    // ���Ƶķ�����ID
    TUserId  m_nSenderId;
    // ���󴫵ݵ�����ID
    TTokenId m_nTokenId;
};


/*====================================================================
���� �� CMcsTokenGiveResponse
���� �� �������ƻظ�ԭ��
====================================================================*/
class CMcsTokenGiveResponse : public CMsg
{
public:
    CMcsTokenGiveResponse():CMsg(e_Mcs, e_TokenGiveResponse)
    {
    }

    // ������
    TResult m_enumResult;
    // ����״̬
    TTokenStatus m_enumStatus;
};


/*====================================================================
���� �� CMcsTokenGiveConfirm
���� �� ��������ȷ��ԭ��
====================================================================*/
class CMcsTokenGiveConfirm : public CMsg
{
public:
    CMcsTokenGiveConfirm():CMsg(e_Mcs, e_TokenGiveConfirm)
    {
    }

    // ���ݵ�����ID
    TTokenId m_nTokenId;
    // ������
    TResult m_enumResult;
    // ����״̬
    TTokenStatus m_enumStatus;
};


/*====================================================================
���� �� CMcsTokenPleaseRequest
���� �� ������������ԭ��
====================================================================*/
class CMcsTokenPleaseRequest : public CMsg
{
public:
    CMcsTokenPleaseRequest():CMsg(e_Mcs, e_TokenPleaseRequest)
    {
    }

    // ���������ID
    TTokenId m_nTokenId;
};


/*====================================================================
���� �� CMcsTokenPleaseIndication
���� �� ��������ָʾԭ��
====================================================================*/
class CMcsTokenPleaseIndication : public CMsg
{
public:
    CMcsTokenPleaseIndication():CMsg(e_Mcs, e_TokenPleaseIndication)
    {
    }

    // ������ID
    TUserId  m_nRequesterId;
    // ���������ID
    TTokenId m_nTokenId;
};


/*====================================================================
���� �� CMcsTokenReleaseRequest
���� �� �ͷ���������ԭ��
====================================================================*/
class CMcsTokenReleaseRequest : public CMsg
{
public:
    CMcsTokenReleaseRequest():CMsg(e_Mcs, e_TokenReleaseRequest)
    {
    }

    // �����ͷ���ID
    TUserId  m_nReleaserId;
    // Ҫ�ͷŵ�����ID
    TTokenId m_nTokenId;
};


/*====================================================================
���� �� CMcsTokenReleaseConfirm
���� �� �ͷ�����ȷ��ԭ��
====================================================================*/
class CMcsTokenReleaseConfirm : public CMsg
{
public:
    CMcsTokenReleaseConfirm():CMsg(e_Mcs, e_TokenReleaseConfirm)
    {
    }

    // Ҫ�ͷŵ�����ID
    TTokenId m_nTokenId;
    // ������
    TResult m_enumResult;
    // ����״̬
    TTokenStatus m_enumStatus;
};


/*====================================================================
���� �� CMcsTokenTestRequest
���� �� ������������ԭ��
====================================================================*/
class CMcsTokenTestRequest : public CMsg
{
public:
    CMcsTokenTestRequest():CMsg(e_Mcs, e_TokenTestRequest)
    {
    }

    // Ҫ���Ե�����ID
    TTokenId m_nTokenId;
};


/*====================================================================
���� �� CMcsTokenTestConfirm
���� �� ��������ȷ��ԭ��
====================================================================*/
class CMcsTokenTestConfirm : public CMsg
{
public:
    CMcsTokenTestConfirm():CMsg(e_Mcs, e_TokenTestConfirm)
    {
    }

    // Ҫ���Ե�����ID
    TTokenId    m_nTokenId;
    // ������
    TResult m_enumResult;
    // �����Ƶ�״̬
    TTokenStatus m_enumTokenStatus;
};



/*====================================================================
���� �� CMcsSetFlowControl
���� �� �������ƴ�������
====================================================================*/
class CMcsSetFlowControl : public CMsg
{
public:
    CMcsSetFlowControl():CMsg(e_Mcs, e_SetFlowControl)
    {
    }

    // ���õ�����������λ Byte/s
    s32 m_nFlowBand;
};

/*====================================================================
���� �� CMcsSetFlowControl
���� �� �������ƴ�������
====================================================================*/
class CMcsFlowControlConfirm : public CMsg
{
public:
    CMcsFlowControlConfirm():CMsg(e_Mcs, e_FlowControlConfirm)
    {
    }

    // �����õ�����������λ Byte/s
    s32 m_nFlowBand;
};


/*====================================================================
���� �� CMcsChannelQueryRequest
���� �� �ŵ���Ϣ��ѯ����
====================================================================*/
class CMcsChannelQueryRequest : public CMsg
{
public:
    CMcsChannelQueryRequest():CMsg(e_Mcs, e_ChannelQueryRequest)
    {
    }

    // �����ѯ���ŵ�ID
    TChannelId m_nQueryChannelId;
};


/*====================================================================
���� �� CMcsChannelQueryConfirm
���� �� �ŵ���Ϣ��ѯȷ��
====================================================================*/
class CMcsChannelQueryConfirm : public CMsg
{
public:
    CMcsChannelQueryConfirm():CMsg(e_Mcs, e_ChannelQueryConfirm)
    {
    }

    // �����ѯ���ŵ�ID
    TChannelId m_nQueryChannelId;
    // ������
    TResult m_enumResult;
    // ���ŵ����ڵ���������IP��ַ
    PString m_strFrom;
    // �������Ƿ񱻶����յ�
    bool m_bIsPassive;
};


#endif
