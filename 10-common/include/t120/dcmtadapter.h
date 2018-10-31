/*****************************************************************************
ģ����      : DcMtLib
�ļ���      : DcMtAdapter.h
����ļ�    : DcMtAdapter.cpp 
�ļ�ʵ�ֹ���: ����CDcMtAdapter��,
              �����ṩDcMtLib�ϲ�ʹ�õĽӿ�
              ʵ��DcMtLib���ϲ�Ӧ��ͨѶ���������Ĺ���
����        : �º��
ģ��汾    : V4.0  Copyright(C) 2004-2005 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �ļ��汾        �޸���      �޸�����
2005/05/24  1.0             �º��      ����
******************************************************************************/

#ifndef _DCMTADAPTER_H
#define _DCMTADAPTER_H

#include"kdvtype.h"
#include<ptlib.h>

#include"dcmtlibstruct.h"

/*====================================================================
���� �� CDcMtAdapter
���� �� ʹ��DcmtLib�Ľӿ�
====================================================================*/
class CDcMtAdapter
{
public:
    /*====================================================================
    ������      �� ���캯��
    �������˵���� szNodeIp : IP��ַ(ASCII����)   nIpLen : IP��ַ�ĳ���
                   szNodeAlias : �ڵ�����(UTF8����)   nAliasLen : ���Ƶĳ���
                   szNodeEmail : �ڵ�Email(Unicode����)   nEmailLen : Email�ĳ���
                   szNodeLocation : �ڵ��ַ(Unicode����)   nLocationLen : ��ַ�ĳ���
                   szNodePhone : �绰����(Unicode����)   nPhoneLen : �绰�ĳ���
                   wNodePort : �ڵ�˿ں�
                   ���У��������ݾ����������ַ���'\0'��'\0\0'��
    ====================================================================*/
    CDcMtAdapter(const char* szNodeIp, s32 nIpLen,
                 const char* szNodeAlias, s32 nAliasLen,
                 const char* szNodeEmail, s32 nEmailLen,
                 const char* szNodeLocation, s32 nLocationLen,
                 const char* szNodePhone, s32 nPhoneLen,
                 u16  wNodePort = 1503);
    /*====================================================================
    ������      �� ��������
    ����        ��
    ====================================================================*/
    virtual ~CDcMtAdapter();

///////////////////////////////////////////////////////////////////////
//�������  -- ���нӿ�
///////////////////////////////////////////////////////////////////////
    /*====================================================================
    ������      :IsInitSuccess
    ����        :�Ƿ�ɹ���ʼ��Э��ջ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:g_cApeSap
    �������˵��:��
    ����ֵ˵��  :true : ��ʼ���ɹ�
                 false: ��ʼ��ʧ��
    ====================================================================*/
    bool IsInitSuccess();

    /*====================================================================
    ������      :HostConference
    ����        :���ֻ���
    �㷨ʵ��    :��
    ����ȫ�ֱ���:g_cApeSap
    �������˵��:szConfName, ��������
                 byAppMask,	 Ӧ������
                             ��ֹ�����ڵ�����ĳЩӦ��
                             byAppMask������AppMask��|���������
                             AppMask�μ�Gcc::AppMask�Ķ���
                 pUserData, �ص�����
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool HostConference(const char* szConfName,
                        u8 byAppMask = e_AppAllAllowed,
                        void* pUserData = NULL);
    
    /*====================================================================
    ������      :Query
    ����        :��ѯ�����ն˻�����Ϣ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:g_cApeSap
    �������˵��:szAddr, ���еĽڵ�IP
                 pUserData, �ص�����
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool Query(const char* szAddr,
                void* pUserData = NULL);
    
    /*====================================================================
    ������      :JoinConference
    ����        :�������Զ�˵Ļ���
    �㷨ʵ��    :��
    ����ȫ�ֱ���:g_cApeSap
    �������˵��:szAddr, Զ�˽ڵ��IP��ַ
                 szConfName, ��������
                 szPwd, ������������
                 pUserData, �ص�����
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool JoinConference(const char* szAddr,
                        const char* szConfName, 
                        const char* szPwd = "",
                        void* pUserData = NULL);

    /*====================================================================
    ������      :InviteMt
    ����        :����ڵ�������
    �㷨ʵ��    :��
    ����ȫ�ֱ���:g_cApeSap
    �������˵��:szConfName,������
                 szAddr, Զ�˽ڵ��IP��ַ
                 pUserData, �ص�����
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool InviteMt(const char* szConfName,
                  const char* szAddr,
                  void* pUserData = NULL);
    /*====================================================================
    ������      :EjectUser
    ����        :�߳��ڵ�
    �㷨ʵ��    :��
    ����ȫ�ֱ���:g_cApeSap
    �������˵��:nNodeID,�ڵ��û�ID
                 pUserData, �ص�����
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool EjectUser(NodeID nNodeID,
                   void* pUserData = NULL);

    /*====================================================================
    ������      :HangUp
    ����        :�Ҷ�
    �㷨ʵ��    :��
    ����ȫ�ֱ���:g_cApeSap
    �������˵��:
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool HangUp();

    /*====================================================================
    ������      :JoinResponse
    ����        :��������������Ӧ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:g_cApeSap
    �������˵��:nTag, Զ�˽ڵ��ʾ
                 enumResult,�Ƿ�����������
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool JoinResponse(u32 nTag, EConferenceResponseResult enumResult);

    /*====================================================================
    ������      :InviteResponse
    ����        :��������������Ӧ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:g_cApeSap
    �������˵��:nTag, Զ�˽ڵ�ı�ʾ
                 enumResult,�Ƿ��������
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool InviteResponse(u32 nTag, EConferenceResponseResult enumResult);

    /*====================================================================
    ������      :SetFlowControl
    ����        :������������
    �㷨ʵ��    :��
    ����ȫ�ֱ���:g_cApeSap
    �������˵��:nFlowBandwidth ��������
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool SetFlowControl(s32 nFlowBandwidth);

///////////////////////////////////////////////////////////////////////
//�������  -- ������Ӧ����
///////////////////////////////////////////////////////////////////////    
    /*====================================================================
    ������      :OnCreateConfirm
    ����        :��������ظ�
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:strFrom,��������Ŀ��ڵ��ַ
                 enumResult,�ظ�
                 bLocalCrate,�Ƿ��ڱ��ش�������
                 pUserData,�û�����
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnCreateConfirm(const PString& strFrom,
                                 EConferenceResponseResult enumResult ,
                                 bool bLocalCreate) = 0;

    /*====================================================================
    ������      :OnQueryResponse
    ����        :����Զ�˻ظ������б�
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:strFrom,Զ��IP��ַ
                 enumResult,�������
                 enumENodeType,Զ�˽ڵ�����
                 pcConfDesc,����ṹ
                 wConfNum,��������
                 pUserData,�û�����
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnQueryResponse(const PString& strFrom,
                                EConferenceResponseResult enumResult,
                                ENodeType enumENodeType,
                                const PString* pstrConfName,
                                u16 wConfNum) = 0;

    /*====================================================================
    ������      :OnJoinConfirm
    ����        :�������ظ�
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:strFrom,����ڵ��ַ
                 enumResult,�ظ�
                 pUserData,�û�����
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnJoinConfirm(const PString& strFrom ,
                                EConferenceResponseResult enumResult) = 0;

    /*====================================================================
    ������      :OnJoinRequest
    ����        :�����ڵ��������
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nFromTag,�������ڵ��ʾ
                 strMtAlias,��������ڵ����
                 strPassword,����
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnJoinRequest( u32 nFromTag ,
                                const PString &strMtAlias,
                                const PString& strPassword) = 0;

    /*====================================================================
    ������      :OnInviteConfirm
    ����        :���ڵ�������
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:strFrom,����Դ�ڵ��ַ
                 enumResult,������
                 pUserData,�û�����
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnInviteConfirm(const PString& strFrom ,
                                EConferenceResponseResult enumResult ) = 0;

    /*====================================================================
    ������      :OnInviteRequest
    ����        :Զ���������
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nFromTag,��������ڵ��ʾ
                 strMtAlias,��������ڵ����
                 cConfDesc,����ṹ
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnInviteRequest(u32 nFromTag,
                                 const PString &strMtAlias,
                                 const PString &strConfName) = 0;

    /*====================================================================
    ������      :OnEjectUserIndication
    ����        :���ڵ���б�����
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:enumReason,���б�����ԭ��
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnEjectUserIndication(EEjectUserReason enumReason) = 0;

    /*====================================================================
    ������      :OnEjectUserConfirm
    ����        :�����ڵ���н���
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nNodeId,���������нڵ�ID
                 enumResult,�������лظ�
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnEjectUserConfirm(NodeID nNodeId,
                                    EEjectUserResult enumResult) = 0;

    /*====================================================================
    ������      :OnNodeAddIndication
    ����        :�ڵ�������
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nNodeId,�������ڵ�ID
                 strFrom,Դ��ַ
                 enumNodePos,�ڵ��߼�λ��
                 strName,�ڵ����
                 strEmail,�ڵ�Email��ַ
                 strPhone,�ڵ�绰����
                 strLocation,�ڵ�����λ��
                 pUserData,�û�����
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnNodeAddIndication(NodeID nNodeId ,
                                    const PString& strFrom ,
                                    EConfNodePos enumNodePos,
                                    const PString& strName ,
                                    const PString& strEmail,
                                    const PString& strPhone ,
                                    const PString& strLocation) = 0;

    /*====================================================================
    ������      :OnNodeRemoveIndication
    ����        :�ڵ��˳�����֪ͨ�����������ڵ㣩
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nNodeId,�˳��ڵ��û�ID
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnNodeRemoveIndication( NodeID nNodeId ) = 0;

    /*====================================================================
    ������      :OnTerminate
    ����        :���ڵ��˳�����
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:enumReason,�˳�����ԭ��
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnTerminate(EConferenceTerminateReason enumReason) = 0;

///////////////////////////////////////////////////////////////////////
//Ӧ��֪ͨ  -- ������Ӧ����
///////////////////////////////////////////////////////////////////////
    /*====================================================================
    ������      :OnOtherStillImageStart
    ����        :���ڵ�û�������װ�ʱ�������ڵ������˰װ�
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nNodeId�������װ�Ľڵ�
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnOtherStillImageStart(NodeID nNodeId) = 0;

    /*====================================================================
    ������      :OnOtherMBFTStart
    ����        :���ڵ�û�������ļ�����ʱ�������ڵ��������ļ�����
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nNodeId�������ļ�����Ľڵ�
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnOtherMBFTStart(NodeID nNodeId) = 0;

    /*====================================================================
    ������      :OnOtherMsChatStart
    ����        :���ڵ�û����������ʱ�������ڵ�����������
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nNodeId����������Ľڵ�
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnOtherMsChatStart(NodeID nNodeId) = 0;

    /*====================================================================
    ������      :OnAppDisableIndication
    ����        :Ӧ������֪ͨ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:byAppMask,Ӧ�����룬��&�ϲ���ͬ����
                       �ж� (byAppMask&AppMask)==AppMask
                       ���������˵����App�Ǳ���ֹ��
                       AppMask�μ�Gcc::AppMask�Ķ���
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnAppDisableIndication( const u8 byAppMask ) = 0;

    
///////////////////////////////////////////////////////////////////////
//Ӧ�ó�����Ӧ��  -- ���нӿ�
///////////////////////////////////////////////////////////////////////    
    
    /*====================================================================
    ������      :SetAppShareCapability
    ����        :���ñ��ڵ�������
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:byBitsPerPixel,�������λ��
                 byColorPointerCacheSize,����ϵͳ��껺��
                 wDesktopWidth,���ڵ�������
                 wDesktopHeight,���ڵ�����߶�
    ����ֵ˵��  :��
    ====================================================================*/
    void SetAppShareCapability(u8 byBitsPerPixel , 
                              u8 byColorPointerCacheSize , 
                              u16 wDesktopWidth , 
                              u16 wDesktopHeight);

    /*====================================================================
    ������      :UpdateAppShareCapability
    ����        :�����и��±��ڵ�������
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:byBitsPerPixel,�������λ��
                 byColorPointerCacheSize,����ϵͳ��껺��
                 wDesktopWidth,���ڵ�������
                 wDesktopHeight,���ڵ�����߶�
    ����ֵ˵��  :��
    ====================================================================*/
    void UpdateAppShareCapability(u8 byBitsPerPixel , 
                                 u8 byColorPointerCacheSize , 
                                 u16 wDesktopWidth , 
                                 u16 wDesktopHeight);

    /*====================================================================
    ������      :StartAppShare
    ����        :����Ӧ�ó�����
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:wNumberApplications,���������
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool StartAppShare( u16 wNumberApplications );

    /*====================================================================
    ������      :StartDesktopAppShare
    ����        :�������湲��
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:��
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool StartDesktopAppShare( );

    /*====================================================================
    ������      :StopAppShare
    ����        :ֹͣ����
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:��
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool StopAppShare( );

    /*====================================================================
    ������      :UpdateWindowList
    ����        :���´����б�
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:wListTime,�¼����ʱ�䣨���룩
                 ptWindow,�����б���Ϣ
                 wWndNumber,��������
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool UpdateWindowList(u16 wListTime , 
                         TAppShareWindow* ptWindow ,
                         u16 wWndNumber);

    /*====================================================================
    ������      :ActivateHostedWindow,ActivateLocalWindow
    ����        :���»����
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nWindowID,�����ID
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool ActivateHostedWindow( s32 nWindowID );
    bool ActivateLocalWindow( );

    /*====================================================================
    ������      :UpdatePalette
    ����        :���µ�ɫ��
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:pbyPalette,��ɫ����Ϣ��ÿһ����4u8����BLUE-GREEN-RED-RESERVERD���У�
                 wColorNumber,��ɫ����������
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool UpdatePalette(u8* pbyPalette ,
                      u16 wColorNumber );

    /*====================================================================
    ������      :UpdateBitmap
    ����        :����ͼ��
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:wDestLeft,Ŀ��������Ͻ�X����
                 wDestTop,Ŀ��������Ͻ�Y����
                 wDestRight,Ŀ��������½�X����
                 wDestBottom,Ŀ��������½�Y����
                 wWidth ,ͼ�󻺳���
                 wHeight ,ͼ�󻺳�߶�
                 byBitPerPixel ,ÿ������ɫλ����8Ϊ256ɫ��24���24λɫ��
                 pbyBmpData,ͼ�󻺳�
                 wBmpDataLength,ͼ�󻺳峤��
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool UpdateBitmap(u16 wDestLeft ,
                     u16 wDestTop ,
                     u16 wDestRight ,
                     u16 wDestBottom ,
                     u16 wWidth ,
                     u16 wHeight ,
                     u8 byBitPerPixel ,
                     u8* pbyBmpData,
                     u16 wBmpDataLength);

    /*====================================================================
    ������      :UpdateSystemPointer
    ����        :����ϵͳ���
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:dwSystemPointerType,ϵͳ������ͣ�0����꣬0x7f00ϵͳĬ����꣩
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool UpdateSystemPointer( u32 dwSystemPointerType );

    /*====================================================================
    ������      :UpdateColorPointer
    ����        :���·�ϵͳ��꣬����껺����д���µ������״
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:ptColorPointer,��ϵͳ�����״��Ϣ
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool UpdateColorPointer(TAppShareColorPointer* ptColorPointer );

    /*====================================================================
    ������      :UpdateCachePointer
    ����        :���������״(����)
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:wCacheIndex,��ϵͳ��껺������
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool UpdateCachePointer(u16 wCacheIndex);

    /*====================================================================
    ������      :UpdatePointerPosition
    ����        :�������λ��
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:wPositionX,���λ��X����
                 wPositionY,���λ��Y����
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool UpdatePointerPosition(u16 wPositionX ,
                              u16 wPositionY );

    /*====================================================================
    ������      :EnableRC
    ����        :Զ�̿������
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:bEnable,�Ƿ����Զ�̿���
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool EnableRC( bool bEnable = false );

    /*====================================================================
    ������      :ConfirmRC
    ����        :Զ�̿�������ظ�
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,����ڵ�ID
                 wRequestIndex,��������
                 wConfirmIndex,ͬ��Զ�̿�������
                 eConfirmType,�Ƿ����Զ�̿��ƣ����ܾ�ԭ��
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool ConfirmRC(NodeID nInitiator,
                  u16 wRequestIndex,
                  u16 wConfirmIndex,
                  ERcConfirmType eConfirmType );


    /*====================================================================
    ������      :RequestRC
    ����        :����Զ�̿���
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,��ʼ����Ľڵ�ID
                 wRequestIndex,����Զ�̿�������
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool RequestRC(NodeID nInitiator,
                     u16 wRequestIndex);

    /*====================================================================
    ������      :ReleaseRC
    ����        :�������Զ�̿���
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,��ʼ����Ľڵ�ID
                 wRequestIndex,��������
                 wControlIndex,Զ�̿�������
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool ReleaseRC(NodeID nInitiator,
                  u16 wRequestIndex,
                  u16 wControlIndex);

    /*====================================================================
    ������      :MouseMove
                 LMouseDown
                 LMouseUp
                 LMouseDoubleClick
                 RMouseDown
                 RMouseUp
                 RMouseDoubleClick
                 MiddleMouseDown
                 MiddleMouseUp
                 MiddleMouseDoubleClick
    ����        :Զ�̿���������
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,��ʼ����Ľڵ�ID
                 nEventTime,�¼����ʱ�䣨���룩
                 nPointX,���λ�ú�����
                 nPointY,���λ��������
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool MouseMove(NodeID nInitiator,
                    s32 nEventTime,
                    s32 nPointX,
                    s32 nPointY );
    bool LMouseDown(NodeID nInitiator,
                    s32 nEventTime,
                    s32 nPointX,
                    s32 nPointY );
    bool LMouseUp(NodeID nInitiator,
                    s32 nEventTime,
                    s32 nPointX,
                    s32 nPointY );
    bool LMouseDoubleClick(NodeID nInitiator,
                    s32 nEventTime,
                    s32 nPointX,
                    s32 nPointY );
    bool RMouseDown(NodeID nInitiator,
                    s32 nEventTime,
                    s32 nPointX,
                    s32 nPointY );
    bool RMouseUp(NodeID nInitiator,
                    s32 nEventTime,
                    s32 nPointX,
                    s32 nPointY );
    bool RMouseDoubleClick(NodeID nInitiator,
                    s32 nEventTime,
                    s32 nPointX,
                    s32 nPointY );
    bool MiddleMouseDown(NodeID nInitiator,
                    s32 nEventTime,
                    s32 nPointX,
                    s32 nPointY );
    bool MiddleMouseUp(NodeID nInitiator,
                    s32 nEventTime,
                    s32 nPointX,
                    s32 nPointY );
    bool MiddleMouseDoubleClick(NodeID nInitiator,
                    s32 nEventTime,
                    s32 nPointX,
                    s32 nPointY );

    /*====================================================================
    ������      :KeyDown
                 KeyUp
    ����        :Զ�̿��Ƽ��̲���
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,��ʼ����Ľڵ�ID
                 nEventTime,�¼����ʱ�䣨���룩
                 wCode,���̲��������
                 byCodeType     -- �������뷽����1��ASCII�ַ���2�����������
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool KeyDown(NodeID nInitiator,
                 s32 nEventTime,
                 u16 wCode,
                 BYTE byCodeType = 2);
    bool KeyUp(NodeID nInitiator,
               s32 nEventTime,
               u16 wCode,
               BYTE byCodeType = 2);

    /*====================================================================
    ������      :RCActivateHostedWindow
    ����        :Զ�̼����
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,��ʼ����Ľڵ�ID
                 nWindowID,����ID
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool RCActivateHostedWindow( NodeID nInitiator , s32 nWindowID );

    /*====================================================================
    ������      :RCActivateHostedWindow
    ����        :Զ�ָ̻�����
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,��ʼ����Ľڵ�ID
                 nWindowID,����ID
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool RCRestoreHostedWindow( NodeID nInitiator , s32 nWindowID );

///////////////////////////////////////////////////////////////////////
//Ӧ�ó�����Ӧ��  -- ������Ӧ����
///////////////////////////////////////////////////////////////////////  
    /*====================================================================
    ������      :OnAppShareCapabilityNegotiationSuccess
    ����        :�����������ɹ�
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:byBitsPerPixel,�������λ��
                ��С��24ֻ�ܷ���256ɫͼ�����ݣ�����24���Է������24λɫͼ�����ݣ�
                 byMacColorPointerCache,����ϵͳ��껺����
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnAppShareCapabilityNegotiationSuccess( u8 byBitsPerPixel ,
                                                         u8 byMaxColorPointerCache ) = 0;
          
    /*====================================================================
    ������      :OnStartAppShareNotif
    ����        :��ʼ����
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,��ʼ����Ӧ�õĽڵ�ID
                 strNodeName,��ʼ����Ӧ�õ��ն˱���
                 wdesktopWidth,������
                 wdesktopHeight,����߶�
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnStartAppShareNotif( NodeID nInitiator ,
                                        const PString& strNodeName ,
                                        u16 wdesktopWidth ,
                                        u16 wdesktopHeight ) = 0;

    /*====================================================================
    ������      :OnStartDesktopShareNotif
    ����        :��ʼ���湲��
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,��ʼ��������Ľڵ�ID
                 strNodeName,��ʼ����������ն˱���
                 wdesktopWidth,������
                 wdesktopHeight,����߶�
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnStartDesktopShareNotif( NodeID nInitiator ,
                                           const PString& strNodeName ,
                                           u16 wdesktopWidth ,
                                           u16 wdesktopHeight ) = 0;

    /*====================================================================
    ������      :OnStopAppShareNotif
    ����        :��������
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,��ʼ����Ľڵ�ID
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnStopAppShareNotif( NodeID nInitiator ) = 0;

    /*====================================================================
    ������      :OnUpdateWindowList
    ����        :�������б�仯
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,��ʼ����Ľڵ�ID
                 ptWindow,�����б���Ϣ
                 wWndNumber,��������
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnUpdateWindowList( NodeID nInitiator ,
                                    TAppShareWindow* ptWindow ,
                                    u16 wWndNumber) = 0;

    /*====================================================================
    ������      :OnActivateHostedWindow,OnActivateLocalWindow
    ����        :Զ���ն˸��»����֪ͨ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,��ʼ����Ľڵ�ID
                 nWindowID,�����ID
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnActivateHostedWindow(NodeID nInitiator,
                                        s32 nWindowID) = 0;
    virtual void OnActivateLocalWindow(NodeID nInitiator) = 0;

    /*====================================================================
    ������      :OnUpdatePalette
    ����        :��ɫ��仯
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,��ʼ����Ľڵ�ID
                 byPalette,��ɫ����Ϣ��ÿһ����4u8����BLUE-GREEN-RED-RESERVERD���У�
                 wColorNumber,��ɫ����������
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnUpdatePalette( NodeID nInitiator ,
                                  u8* pbyPalette ,
                                  u16 nNumberColor ) = 0;
    
    /*====================================================================
    ������      :OnUpdateBitmap
    ����        :����ͼ��
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,��ʼ����Ľڵ�ID
                 wDestLeft,Ŀ��������Ͻ�X����
                 wDestTop,Ŀ��������Ͻ�Y����
                 wDestRight,Ŀ��������½�X����
                 wDestBottom,Ŀ��������½�Y����
                 wWidth ,ͼ�󻺳���
                 wHeight ,ͼ�󻺳�߶�
                 byBitPerPixel ,ÿ������ɫλ����8Ϊ256ɫ��24���24λɫ��
                 pbyBmpData,ͼ�󻺳�
                 wBmpDataLength,ͼ�󻺳峤��
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnUpdateBitmap(NodeID nInitiator ,
                                u16 wDestLeft ,
                                u16 wDestTop ,
                                u16 wDestRight ,
                                u16 wDestBottom ,
                                u16 wWidth ,
                                u16 wHeight ,
                                u8 byBitPerPixel ,
                                u8* pbyBmpData,
                                u16 wBmpDataLength) = 0;

    /*====================================================================
    ������      :OnUpdateCapability
    ����        :���������߸���������
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,��ʼ��������Ľڵ�ID
                 strNodeName,��ʼ����������ն˱���
                 wdesktopWidth,������
                 wdesktopHeight,����߶�
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnUpdateCapability( NodeID nInitiator ,
                                    const PString& strNodeName , 
                                    u16 wdesktopWidth ,
                                    u16 wdesktopHeight ) = 0;

    /*====================================================================
    ������      :OnUpdateSystemPointer
    ����        :����ϵͳ���
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,��ʼ����Ľڵ�ID
                 dwSystemPointerType,ϵͳ������ͣ�0����꣬0x7f00ϵͳĬ����꣩
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnUpdateSystemPointer( NodeID nInitiator ,
                                        u32 dwSystemPointerType ) = 0;

    /*====================================================================
    ������      :OnUpdateColorPointer
    ����        :���·�ϵͳ��꣬����껺����д���µ������״
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,��ʼ����Ľڵ�ID
                 ptColorPointer,��ϵͳ�����״��Ϣ
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnUpdateColorPointer( NodeID nInitiator ,
                                       TAppShareColorPointer* ptColorPointer ) = 0;
    
    /*====================================================================
    ������      :OnUpdateCachePointer
    ����        :���·�ϵͳ������꣬��ʾʹ�ø����������
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,��ʼ����Ľڵ�ID
                 wCacheIndex,��ϵͳ�����������
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnUpdateCachePointer( NodeID nInitiator ,
                                       u16 wCacheIndex ) = 0;

    /*====================================================================
    ������      :OnUpdatePointerPosition
    ����        :���»���λ��
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,��ʼ����Ľڵ�ID
                 wPositionX,��������
                 wPositionY,���������
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnUpdatePointerPosition( NodeID nInitiator ,
                                          u16 wPositionX ,
                                          u16 wPositionY ) = 0;
    
    /*====================================================================
    ������      :OnEnableRC
    ����        :Զ�̿������
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,��ʼ����Ľڵ�ID
                 bEnalbe,Զ�̿������
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnEnableRC( NodeID nInitiator ,
                             bool bEnable ) = 0;

    /*====================================================================
    ������      :OnOtherRCing
    ����        :�����ն��Ѿ�Զ�̿���ָ������
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,��ʼ����Ľڵ�ID
                 nControlId,Զ�̿��ƹ���Ľڵ�ID
                 strName,��ǰ�����ն˱���
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnOtherRCing( NodeID nInitiator ,
                               NodeID nControlId , 
                               const PString& strName ) = 0;

    /*====================================================================
    ������      :OnRequestRC
    ����        :Զ���ն�����Զ�̿��ƣ����̷��أ�
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,����Զ�̿��ƽڵ�ID
                 strName,��������ն˱���
                 wRequestIndex,�����ն�����
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnRequestRC(NodeID nInitiator,
                             const PString& strNodeName ,
                             u16 wRequestIndex ) = 0;
    /*====================================================================
    ������      :OnConfirmRC
    ����        :����Զ�̿��ƻظ�
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,��ʼ����Ľڵ�ID
                 wRequestIndex,����Զ�̿��Ƶ�����
                 wConfirmIndex,����õ�����Ȩ��ΪԶ�̿��������������������Ȩ����Ҫ��
                 enumConfirmType,�ظ����
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnConfirmRC( NodeID nInitiator ,
                              u16 wRequestIndex ,
                              u16 wConfirmIndex ,
                              ERcConfirmType enumConfirmType ) = 0;
    /*====================================================================
    ������      :OnReleaseRC
    ����        :Զ���ն��������Զ�̿��ƣ����̷��أ�
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,����Զ�̿��ƽڵ�ID
                 wRequestIndex,�����ն�����
                 wConfirmIndex,����ɹ�ʱ�õ���ͬ��Զ�̿�������
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnReleaseRC(NodeID nInitiator,
                            u16 wRequestIndex,
                            u16 wConfirmIndex) = 0;

    /*====================================================================
    ������      :OnMouseMove
                 OnLMouseDown
                 OnLMouseUp
                 OnLMouseDoubleClick
                 OnRMouseDown
                 OnRMouseUp
                 OnRMouseDoubleClick
                 OnMiddleMouseDown
                 OnMiddleMouseUp
                 OnMiddleMouseDoubleClick
    ����        :Զ�̿���������
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,Զ�̿��ƽڵ�ID
                 nEventTime,�¼����ʱ�䣨���룩
                 nPointX,���λ���߼�������
                 nPointY,���λ���߼�������
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnMouseMove(NodeID nInitiator,
                            s32 nEventTime,
                            s32 nPointX,
                            s32 nPointY ) = 0;
    virtual void OnLMouseDown(NodeID nInitiator,
                              s32 nEventTime,
                              s32 nPointX,
                              s32 nPointY ) = 0;
    virtual void OnLMouseUp(NodeID nInitiator,
                            s32 nEventTime,
                            s32 nPointX,
                            s32 nPointY ) = 0;
    virtual void OnLMouseDoubleClick(NodeID nInitiator,
                                    s32 nEventTime,
                                    s32 nPointX,
                                    s32 nPointY ) = 0;
    virtual void OnRMouseDown(NodeID nInitiator,
                                s32 nEventTime,
                                s32 nPointX,
                                s32 nPointY ) = 0;
    virtual void OnRMouseUp(NodeID nInitiator,
                            s32 nEventTime,
                            s32 nPointX,
                            s32 nPointY ) = 0;
    virtual void OnRMouseDoubleClick(NodeID nInitiator,
                                    s32 nEventTime,
                                    s32 nPointX,
                                    s32 nPointY ) = 0;
    virtual void OnMiddleMouseDown(NodeID nInitiator,
                                    s32 nEventTime,
                                    s32 nPointX,
                                    s32 nPointY ) = 0;
    virtual void OnMiddleMouseUp(NodeID nInitiator,
                                s32 nEventTime,
                                s32 nPointX,
                                s32 nPointY ) = 0;
    virtual void OnMiddleMouseDoubleClick(NodeID nInitiator,
                                            s32 nEventTime,
                                            s32 nPointX,
                                            s32 nPointY ) = 0;

    /*====================================================================
    ������      :OnKeyDown
                 OnKeyUp
    ����        :Զ�̿��Ƽ��̲���
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,Զ�̿��ƽڵ�ID
                 nEventTime,�¼����ʱ�䣨���룩
                 byCodeType,�������뷽����1��ASCII�ַ���2�����������
                 wCode,��ֵ
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnKeyDown(NodeID nInitiator,
                            s32 nEventTime,
                            u8 byCodeType,
                            u16 wCode) = 0;
    virtual void OnKeyUp(NodeID nInitiator,
                        s32 nEventTime,
                        u8 byCodeType,
                        u16 wCode) = 0;

    /*====================================================================
    ������      :OnRCActivateHostedWindow
    ����        :Զ�̿����л�Hosted�����
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,��ʼ����Ľڵ�ID
                 nWindowID,�����ID
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnRCActivateHostedWindow( NodeID nInitiator,
                                           s32 nWindowID ) = 0;

    /*====================================================================
    ������      :OnRCRestoreHostedWindow
    ����        :����ӱ����������Hosted����
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,��ʼ����Ľڵ�ID
                 nWindowID,�����ID
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnRCRestoreHostedWindow(NodeID nInitiator,
                                         s32 nWindowID ) = 0;
    

///////////////////////////////////////////////////////////////////////
//���Ӱװ�Ӧ��  -- ���нӿں���
///////////////////////////////////////////////////////////////////////  

    /*====================================================================
    ������      :StartStillImage
    ����        :�������������Ӱװ�Ӧ��
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:bSupportText,�Ƿ�֧������
                 bSupport24Bitmap,�Ƿ�֧��24λ���ɫͼ��
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool StartStillImage( bool bSupportText = true ,
                         bool bSupport24Bitmap = true );

    /*====================================================================
    ������      :StopStillImage
    ����        :������ֹͣ���Ӱװ�Ӧ��
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool StopStillImage( );

    /*====================================================================
    ������      :RefreshWorkspaceStatus
    ����        :ˢ�¹�����״̬
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:bRefresh,һ��Ϊtrue
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool RefreshWorkspaceStatus( bool bRefresh = true );

    /*====================================================================
    ������      :CreateWorkspace
    ����        :�½�������
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:tWorkspace,������ṹ��Ϣ
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool CreateWorkspace( const TStillImageWorkspace& tWorkspace );

    /*====================================================================
    ������      :DeleteWorkspace
    ����        :ɾ��������
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nWorkspaceHandle,��������
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool DeleteWorkspace( s32 nWorkspaceHandle );

    /*====================================================================
    ������      :EditWorkspaceViewViewState
    ����        :�޸Ĺ�������ͼ״̬
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nWorkspaceHandle,��������
                 nViewHandle,��ͼ���
                 enumViewState,��ͼ״̬
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool EditWorkspaceViewViewState( s32 nWorkspaceHandle ,
                                    s32 nViewHandle ,
                                    TStillImageViewParameter::ViewState enumViewState );

    /*====================================================================
    ������      :EditWorkspaceViewUpdateEnabled
    ����        :�޸Ĺ�������ͼ����״̬
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nWorkspaceHandle,��������
                 nViewHandle,��ͼ���
                 bUpdateEnabled,��ͼ����״̬
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool EditWorkspaceViewUpdateEnabled( s32 nWorkspaceHandle ,
                                        s32 nViewHandle ,
                                        bool bUpdateEnabled );

    /*====================================================================
    ������      :CreateDrawing
    ����        :�½�ͼ��
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:tDrawing,ͼ�νṹ��Ϣ
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool CreateDrawing( const TStillImageDrawing& tDrawing );

    /*====================================================================
    ������      :DeleteDrawing
    ����        :ɾ��ͼ��
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nDrawingHandle,ͼ�ξ��
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool DeleteDrawing( s32 nDrawingHandle );

    /*====================================================================
    ������      :EditDrawingPenColor
    ����        :�༭ͼ�α���ɫ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nDrawingHandle,ͼ�ξ��
                 tPenColor,����ɫ
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool EditDrawingPenColor( s32 nDrawingHandle ,
                             const TStillImageColorRGB& tPenColor );

    /*====================================================================
    ������      :EditDrawingFillColor
    ����        :�༭ͼ�����ɫ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nDrawingHandle,ͼ�ξ��
                 tFillColor,���ɫ
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool EditDrawingFillColor( s32 nDrawingHandle ,
                              const TStillImageColorRGB& tFillColor );

    /*====================================================================
    ������      :EditDrawingPenThickness
    ����        :�༭ͼ�αʿ��
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nDrawingHandle,ͼ�ξ��
                 byPenThickness,�ʿ��
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool EditDrawingPenThickness( s32 nDrawingHandle ,
                                 u8 byPenThickness );

    /*====================================================================
    ������      :EditDrawingPenNib
    ����        :�༭ͼ�α���״
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nDrawingHandle,ͼ�ξ��
                 enumPenNib,����״
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool EditDrawingPenNib( s32 nDrawingHandle ,
                           TStillImageDrawing::PenNib enumPenNib );

    /*====================================================================
    ������      :EditDrawingLineStyle
    ����        :�༭ͼ������
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nDrawingHandle,ͼ�ξ��
                 enumLineStyle,����
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool EditDrawingLineStyle( s32 nDrawingHandle ,
                              TStillImageDrawing::LineStyle enumLineStyle );

    /*====================================================================
    ������      :EditDrawingHighlight
    ����        :�༭ͼ�θ�����ʾ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:
                 
    �������˵��:nDrawingHandle,ͼ�ξ��
                 bHighlight,�Ƿ������ʾ
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool EditDrawingHighlight( s32 nDrawingHandle ,
                              bool bHighlight );

    /*====================================================================
    ������      :EditDrawingViewState
    ����        :�༭ͼ����ͼ״̬
    �㷨ʵ��    :��
    ����ȫ�ֱ���:
                 
    �������˵��:nDrawingHandle,ͼ�ξ��
                 enumViewState,��ͼ״̬
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool EditDrawingViewState( s32 nDrawingHandle ,
                              TStillImageDrawing::ViewState enumViewState );

    /*====================================================================
    ������      :EditDrawingZOrder
    ����        :�༭ͼ��Z�����λ��
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nDrawingHandle,ͼ�ξ��
                 enumZOrder,Z�����λ��
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool EditDrawingZOrder( s32 nDrawingHandle ,
                           TStillImageDrawing::ZOrder enumZOrder );

    /*====================================================================
    ������      :EditDrawingAnchorPoint
    ����        :�ƶ�ͼ��
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nDrawingHandle,ͼ�ξ��
                 tAnchorPoint,ͼ�λ�������
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool EditDrawingAnchorPoint( s32 nDrawingHandle ,
                                const TStillImagePoint& tAnchorPoint );

    /*====================================================================
    ������      :EditDrawingSubPoints
    ����        :�༭ͼ����״
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nDrawingHandle,ͼ�ξ��
                 nInitialIndex,��ʼ����
                 tInitialPoint,��ʼ������
                 nSubPointsNum,ͼ����ϵ���Ŀ
                 ptPoints,ͼ����ϵ㼯��
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool EditDrawingSubPoints( s32 nDrawingHandle ,
                              s32 nInitialIndex ,
                              const TStillImagePoint& tInitialPoint ,
                              s32 nSubPointsNum ,
                              const TStillImagePoint* ptPoints );

    /*====================================================================
    ������      :CreateBitmap
    ����        :�½�ͼƬ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:tBmp,ͼƬ�ṹ��Ϣ
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool CreateBitmap( const TStillImageBitmap& tBmp );

    /*====================================================================
    ������      :CreateBitmapPointer
    ����        :�½�Զ��ָʾ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:
                 
    �������˵��:tBmp,ͼƬ�ṹ��Ϣ
                 nTransparencyMaskLength,���볤��
                 pbyTransparencyMask,��������
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool CreateBitmapPointer( const TStillImageBitmap& tBmp ,
                            s32 nTransparencyMaskLength ,
                            const u8* pbyTransparencyMask );

    /*====================================================================
    ������      :CreateBitmapContinue
    ����        :�½�ͼƬ��������
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nBitmapHandle,ͼƬ���
                 bMoreToFollow,�Ƿ��к�������(Ϊfalse��ʾͼƬ����������)
                 nBitmapDataLength,ͼƬ���ݳ���
                 pbyBitmapData,ͼƬ����
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool CreateBitmapContinue( s32 nBitmapHandle ,
                              bool bMoreToFollow ,
                              s32 nBitmapDataLength ,
                              const u8* pbyBitmapData );

    /*====================================================================
    ������      :DeleteBitmap
    ����        :ɾ��ͼƬ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nBitmapHandle,ͼƬ���
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool DeleteBitmap( s32 nBitmapHandle );

    /*====================================================================
    ������      :EditBitmapViewState
    ����        :�༭ͼƬ��ͼ״̬
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nBitmapHandle,ͼƬ���
                 enumViewState,��ͼ״̬
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool EditBitmapViewState( s32 nBitmapHandle ,
                             TStillImageBitmap::ViewState enumViewState );

    /*====================================================================
    ������      :EditBitmapZOrder
    ����        :�༭ͼƬZ�����λ��
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nBitmapHandle,ͼƬ���
                 enumZOrder,Z�����λ��
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool EditBitmapZOrder( s32 nBitmapHandle ,
                          TStillImageBitmap::ZOrder enumZOrder );

    /*====================================================================
    ������      :EditBitmapAnchorPoint
    ����        :�ƶ�ͼƬλ��
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nBitmapHandle,ͼƬ���
                 tAnchorPoint,ͼƬ��������
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool EditBitmapAnchorPoint( s32 nBitmapHandle ,
                               const TStillImagePoint& tAnchorPoint );

    /*====================================================================
    ������      :CreateText
    ����        :�½�����
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:tText,���ֽṹ��Ϣ
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool CreateText( const TStillImageText& tText );

    /*====================================================================
    ������      :DeleteText
    ����        :ɾ������
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nTextHandle,���־��
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool DeleteText( s32 nTextHandle );

    /*====================================================================
    ������      :EditTextTextData
    ����        :�ı���������
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nTextHandle,���־��
                 nTextDataLength,���ֳ���
                 pbyTextData,��������
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool EditTextTextData( s32 nTextHandle ,
                          s32 nTextDataLength ,
                          const u8* pbyTextData );

    /*====================================================================
    ������      :EditTextTextStyle
    ����        :�ı����ָ�ʽ���༭״̬�����ǷǱ༭״̬Ҳ��ʹ�ã�
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nTextHandle,���־��
                 tTextColor,������ɫ
                 tLogfont,��������
                 nTextDataLength,���ֳ���
                 pbyTextData,��������
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool EditTextTextStyle( s32 nTextHandle ,
                           const TStillImageColorRGB& tTextColor ,
                           const TStillImageLogfont& tLogfont ,
                           s32 nTextDataLength ,
                           const u8* pbyTextData );

    /*====================================================================
    ������      :EditTextTextColor
    ����        :�ı�������ɫ���༭״̬�����ǷǱ༭״̬Ҳ��ʹ�ã�
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nTextHandle,���־��
                 tTextColor,������ɫ
                 nTextDataLength,���ֳ���
                 pbyTextData,��������
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool EditTextTextColor( s32 nTextHandle ,
                           const TStillImageColorRGB& tTextColor ,
                           s32 nTextDataLength ,
                           const u8* pbyTextData );

    /*====================================================================
    ������      :EditTextViewState
    ����        :�༭������ͼ״̬
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nTextHandle,���־��
                 enumViewState,��ͼ״̬
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool EditTextViewState( s32 nTextHandle ,
                           TStillImageText::ViewState enumViewState );

    /*====================================================================
    ������      :EditTextZOrder
    ����        :�༭����Z�����λ��
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nTextHandle,���־��
                 enumZOrder,Z�����λ��
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool EditTextZOrder( s32 nTextHandle ,
                        TStillImageText::ZOrder enumZOrder );

    /*====================================================================
    ������      :EditTextAnchorPoint
    ����        :�ƶ�����
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nTextHandle,���־��
                 tAnchorPoint,���ֻ���
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool EditTextAnchorPoint( s32 nTextHandle ,
                             const TStillImagePoint& tAnchorPoint );

///////////////////////////////////////////////////////////////////////
//���Ӱװ�Ӧ��  -- ������Ӧ����
///////////////////////////////////////////////////////////////////////  
    /*====================================================================
    ������      :OnStillImageCapabilityNegotiationSuccess
    ����        :�����������ɹ�֪ͨ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nParticipantsNum,�����п����װ�Ӧ�õ��ն���
                 pnParticipantsNodeList,�����װ�Ӧ�õ��ն��б�һά����
                 bSupportText,�ն˰װ�Ӧ���Ƿ�֧������
                 bSupport24Bitmap,�ն˰װ�Ӧ���Ƿ�֧��24λɫ���ͼƬ
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnStillImageCapabilityNegotiationSuccess(s32 nParticipantsNum ,
                                                          NodeID *pnParticipantsNodeList,
                                                          bool bSupportText ,
                                                          bool bSupport24Bitmap ) = 0;
    
    /*====================================================================
    ������      :OnWorkspaceRefreshStatus
    ����        :������״̬ˢ��֪ͨ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,����������ն˰װ�Ӧ��ID
                 bRefresh,һ��Ϊtrue
                 bLocalOperate,�Ƿ��ն˷���Ĳ���(���Ϊtrue,�����Ϊ�����ն˼���Ӧ��
                                �ϲ���Ҫ�����й����估����������ͼ��Ԫ�ص����·���һ��)
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnWorkspaceRefreshStatus( NodeID nInitiator ,
                                            bool bRefresh ,
                                            bool bLocalOperate ) = 0;

    /*====================================================================
    ������      :OnWorkspaceCreate
    ����        :�������½�֪ͨ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,����������ն˰װ�Ӧ��ID
                 tWorkspace,������ṹ��Ϣ
                 bLocalOperate,�Ƿ��ն˷���Ĳ���
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnWorkspaceCreate( NodeID nInitiator ,
                                    const TStillImageWorkspace& tWorkspace ,
                                    bool bLocalOperate ) = 0;

    /*====================================================================
    ������      :OnWorkspaceDelete
    ����        :������ɾ��֪ͨ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,����������ն˰װ�Ӧ��ID
                 nWorkspaceHandle,��������
                 bLocalOperate,�Ƿ��ն˷���Ĳ���
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnWorkspaceDelete( NodeID nInitiator ,
                                    s32 nWorkspaceHandle ,
                                    bool bLocalOperate ) = 0;

    /*====================================================================
    ������      :OnWorkspaceEditCreateView
    ����        :��������ͼ����֪ͨ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,����������ն˰װ�Ӧ��ID
                 nWorkspaceHandle,��������
                 tViewParameter,��������ͼ�ṹ��Ϣ
                 bLocalOperate,�Ƿ��ն˷���Ĳ���
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnWorkspaceEditCreateView( NodeID nInitiator ,
                                            s32 nWorkspaceHandle ,
                                            const TStillImageViewParameter& tViewParameter ,
                                            bool bLocalOperate ) = 0;

    /*====================================================================
    ������      :OnWorkspaceEditViewState
    ����        :��������ͼ״̬�仯֪ͨ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,����������ն˰װ�Ӧ��ID
                 nWorkspaceHandle,��������
                 nViewHandle,��������ͼ���
                 enumViewState,��������ͼ״̬
                 bLocalOperate,�Ƿ��ն˷���Ĳ���
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnWorkspaceEditViewState( NodeID nInitiator ,
                                           s32 nWorkspaceHandle ,
                                           s32 nViewHandle,
                                           TStillImageViewParameter::ViewState enumViewState ,
                                           bool bLocalOperate ) = 0;

    /*====================================================================
    ������      :OnWorkspaceEditViewUpdateEnabled
    ����        :��������ͼ����״̬�仯֪ͨ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,����������ն˰װ�Ӧ��ID
                 nWorkspaceHandle,��������
                 nViewHandle,��������ͼ���
                 bUpdatesEnabled,�Ƿ�����(Ϊtrue,��ʾ��ˢ��,δ������;Ϊfalse,��ʾ����ˢ��,������)
                 bLocalOperate,�Ƿ��ն˷���Ĳ���
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnWorkspaceEditViewUpdateEnabled( NodeID nInitiator ,
                                                   s32 nWorkspaceHandle ,
                                                   s32 nViewHandle,
                                                   bool bUpdatesEnabled,
                                                   bool bLocalOperate ) = 0;

    /*====================================================================
    ������      :OnDrawingCreate
    ����        :ͼ���½�֪ͨ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,����������ն˰װ�Ӧ��ID
                 tDrawing,ͼ�νṹ��Ϣ
                 bLocalOperate,�Ƿ��ն˷���Ĳ���
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnDrawingCreate( NodeID nInitiator ,
                                  const TStillImageDrawing& tDrawing ,
                                  bool bLocalOperate ) = 0;
    
    /*====================================================================
    ������      :OnDrawingDelete
    ����        :ͼ��ɾ��֪ͨ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,����������ն˰װ�Ӧ��ID
                 nDrawingHandle,ͼ�ξ��
                 bLocalOperate,�Ƿ��ն˷���Ĳ���
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnDrawingDelete( NodeID nInitiator ,
                                  s32 nDrawingHandle ,
                                  bool bLocalOperate ) = 0;

    /*====================================================================
    ������      :OnDrawingEditPenColor
    ����        :ͼ�α���ɫ�仯֪ͨ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,����������ն˰װ�Ӧ��ID
                 nDrawingHandle,ͼ�ξ��
                 tPenColor,����ɫ
                 bLocalOperate,�Ƿ��ն˷���Ĳ���
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnDrawingEditPenColor( NodeID nInitiator ,
                                        s32 nDrawingHandle ,
                                        const TStillImageColorRGB& tPenColor ,
                                        bool bLocalOperate ) = 0;

    /*====================================================================
    ������      :OnDrawingEditFillColor
    ����        :ͼ�����ɫ�仯֪ͨ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,����������ն˰װ�Ӧ��ID
                 nDrawingHandle,ͼ�ξ��
                 tFillColor,���ɫ
                 bLocalOperate,�Ƿ��ն˷���Ĳ���
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnDrawingEditFillColor( NodeID nInitiator ,
                                        s32 nDrawingHandle ,
                                        const TStillImageColorRGB& tFillColor ,
                                        bool bLocalOperate ) = 0;

    /*====================================================================
    ������      :OnDrawingEditPenThickness
    ����        :ͼ�αʿ�ȱ仯֪ͨ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,����������ն˰װ�Ӧ��ID
                 nDrawingHandle,ͼ�ξ��
                 byPenThickness,�ʿ��
                 bLocalOperate,�Ƿ��ն˷���Ĳ���
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnDrawingEditPenThickness( NodeID nInitiator ,
                                            s32 nDrawingHandle ,
                                            u8 byPenThickness ,
                                            bool bLocalOperate ) = 0;

    /*====================================================================
    ������      :OnDrawingEditPenNib
    ����        :ͼ�αʼ���״�仯֪ͨ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,����������ն˰װ�Ӧ��ID
                 nDrawingHandle,ͼ�ξ��
                 enumPenNib,�ʼ���״
                 bLocalOperate,�Ƿ��ն˷���Ĳ���
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnDrawingEditPenNib( NodeID nInitiator ,
                                      s32 nDrawingHandle ,
                                      TStillImageDrawing::PenNib enumPenNib ,
                                      bool bLocalOperate ) = 0;

    /*====================================================================
    ������      :OnDrawingEditLineStyle
    ����        :ͼ�����α仯֪ͨ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,����������ն˰װ�Ӧ��ID
                 nDrawingHandle,ͼ�ξ��
                 enumLineStyle,����
                 bLocalOperate,�Ƿ��ն˷���Ĳ���
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnDrawingEditLineStyle( NodeID nInitiator ,
                                        s32 nDrawingHandle ,
                                        TStillImageDrawing::LineStyle enumLineStyle ,
                                        bool bLocalOperate ) = 0;

    /*====================================================================
    ������      :OnDrawingEditHighlight
    ����        :ͼ�θ�����ʾ�仯֪ͨ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,����������ն˰װ�Ӧ��ID
                 nDrawingHandle,ͼ�ξ��
                 bHighlight,�Ƿ������ʾ
                 bLocalOperate,�Ƿ��ն˷���Ĳ���
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnDrawingEditHighlight( NodeID nInitiator ,
                                        s32 nDrawingHandle ,
                                        bool bHighlight ,
                                        bool bLocalOperate ) = 0;

    /*====================================================================
    ������      :OnDrawingEditViewState
    ����        :ͼ����ͼ״̬�仯֪ͨ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,����������ն˰װ�Ӧ��ID
                 nDrawingHandle,ͼ�ξ��
                 enumViewState,ͼ����ͼ״̬
                 bLocalOperate,�Ƿ��ն˷���Ĳ���
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnDrawingEditViewState( NodeID nInitiator ,
                                        s32 nDrawingHandle ,
                                        TStillImageDrawing::ViewState enumViewState ,
                                        bool bLocalOperate ) = 0;

    /*====================================================================
    ������      :OnDrawingEditZOrder
    ����        :ͼ��Z�����λ�ñ仯֪ͨ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,����������ն˰װ�Ӧ��ID
                 nDrawingHandle,ͼ�ξ��
                 enumZOrder,ͼ��Z�����λ��
                 bLocalOperate,�Ƿ��ն˷���Ĳ���
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnDrawingEditZOrder( NodeID nInitiator ,
                                      s32 nDrawingHandle ,
                                      TStillImageDrawing::ZOrder enumZOrder ,
                                      bool bLocalOperate ) = 0;

    /*====================================================================
    ������      :OnDrawingEditAnchorPoint
    ����        :ͼ���ƶ�֪ͨ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,����������ն˰װ�Ӧ��ID
                 nDrawingHandle,ͼ�ξ��
                 tAnchorPoint,ͼ�ε�һ�����������
                 bLocalOperate,�Ƿ��ն˷���Ĳ���
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnDrawingEditAnchorPoint( NodeID nInitiator ,
                                           s32 nDrawingHandle ,
                                           const TStillImagePoint& tAnchorPoint ,
                                           bool bLocalOperate ) = 0;

    /*====================================================================
    ������      :OnDrawingEditSubPoints
    ����        :ͼ����״�༭֪ͨ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,����������ն˰װ�Ӧ��ID
                 nDrawingHandle,ͼ�ξ��
                 nInitialIndex,��ʼ����
                 tInitialPoint,��ʼ�����꣺����Դ���ʱm_tAnchorPoint���������
                 nSubPointsNum,ͼ�β�ֵ����Ŀ
                 ptPoints,ͼ�β�ֵ�㼯�ϣ�ÿһ�����������ǰһ������������
                 bLocalOperate,�Ƿ��ն˷���Ĳ���
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnDrawingEditSubPoints( NodeID nInitiator ,
                                        s32 nDrawingHandle ,
                                        s32 nInitialIndex ,
                                        const TStillImagePoint& tInitialPoint ,
                                        s32 nSubPointsNum ,
                                        const TStillImagePoint* ptPoints ,
                                        bool bLocalOperate ) = 0;

    /*====================================================================
    ������      :OnBitmapCreate
    ����        :ͼƬ�½�֪ͨ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,����������ն˰װ�Ӧ��ID
                 tBmp,ͼƬ�ṹ��Ϣ
                 bLocalOperate,�Ƿ��ն˷���Ĳ���
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnBitmapCreate( NodeID nInitiator ,
                                const TStillImageBitmap& tBmp ,
                                bool bLocalOperate ) = 0;

    /*====================================================================
    ������      :OnBitmapPointerCreate
    ����        :Զ��ָʾ�½�֪ͨ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,����������ն˰װ�Ӧ��ID
                 tBmp,ͼƬ�ṹ��Ϣ
                 nTransparencyMaskLength,���볤��
                 pbyTransparencyMask,��������
                 bLocalOperate,�Ƿ��ն˷���Ĳ���
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnBitmapPointerCreate( NodeID nInitiator ,
                                        const TStillImageBitmap& tBmp ,
                                        s32 nTransparencyMaskLength ,
                                        const u8* pbyTransparencyMask ,
                                        bool bLocalOperate ) = 0;

    /*====================================================================
    ������      :OnBitmapContinue
    ����        :�½�ͼƬ��������
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,����������ն˰װ�Ӧ��ID
                 nBitmapHandle,ͼƬ���
                 bMoreToFollow,�Ƿ��к�������(Ϊfalse��ʾͼƬ����������)
                 nBitmapDataLength,ͼƬ���ݳ���
                 pbyBitmapData,ͼƬ����
                 bLocalOperate,�Ƿ��ն˷���Ĳ���
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnBitmapContinue( NodeID nInitiator ,
                                    s32 nBitmapHandle ,
                                    bool bMoreToFollow ,
                                    s32 nBitmapDataLength ,
                                    const u8* pbyBitmapData ,
                                    bool bLocalOperate ) = 0;

    /*====================================================================
    ������      :OnBitmapDelete
    ����        :ͼƬɾ��֪ͨ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,����������ն˰װ�Ӧ��ID
                 nBitmapHandle,ͼƬ���
                 bLocalOperate,�Ƿ��ն˷���Ĳ���
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnBitmapDelete( NodeID nInitiator ,
                                s32 nBitmapHandle ,
                                bool bLocalOperate ) = 0;

    /*====================================================================
    ������      :OnBitmapEditViewState
    ����        :ͼƬ��ͼ״̬�仯֪ͨ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,����������ն˰װ�Ӧ��ID
                 nBitmapHandle,ͼƬ���
                 enumViewState,ͼƬ��ͼ״̬
                 bLocalOperate,�Ƿ��ն˷���Ĳ���
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnBitmapEditViewState( NodeID nInitiator ,
                                        s32 nBitmapHandle ,
                                        TStillImageBitmap::ViewState enumViewState ,
                                        bool bLocalOperate ) = 0;
    
    /*====================================================================
    ������      :OnBitmapEditZOrder
    ����        :ͼƬZ�����λ�ñ仯֪ͨ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,����������ն˰װ�Ӧ��ID
                 nBitmapHandle,ͼƬ���
                 enumZOrder,Z�����λ��
                 bLocalOperate,�Ƿ��ն˷���Ĳ���
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnBitmapEditZOrder( NodeID nInitiator ,
                                    s32 nBitmapHandle ,
                                    TStillImageBitmap::ZOrder enumZOrder ,
                                    bool bLocalOperate ) = 0;

    /*====================================================================
    ������      :OnBitmapEditAnchorPoint
    ����        :ͼƬ�ƶ�֪ͨ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,����������ն˰װ�Ӧ��ID
                 nBitmapHandle,ͼƬ���
                 tAnchorPoint,��������
                 bLocalOperate,�Ƿ��ն˷���Ĳ���
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnBitmapEditAnchorPoint( NodeID nInitiator ,
                                          s32 nBitmapHandle ,
                                          const TStillImagePoint& tAnchorPoint ,
                                          bool bLocalOperate ) = 0;
    
    /*====================================================================
    ������      :OnTextCreate
    ����        :�����½�֪ͨ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,����������ն˰װ�Ӧ��ID
                 tText,���ֽṹ��Ϣ
                 bLocalOperate,�Ƿ��ն˷���Ĳ���
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnTextCreate( NodeID nInitiator ,
                               const TStillImageText& tText ,
                               bool bLocalOperate ) = 0;

    /*====================================================================
    ������      :OnTextDelete
    ����        :����ɾ��֪ͨ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,����������ն˰װ�Ӧ��ID
                 nTextHandle,���־��
                 bLocalOperate,�Ƿ��ն˷���Ĳ���
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnTextDelete( NodeID nInitiator ,
                               s32 nTextHandle ,
                               bool bLocalOperate ) = 0;
    
    /*====================================================================
    ������      :OnTextEditTextData
    ����        :�������ݸı�֪ͨ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,����������ն˰װ�Ӧ��ID
                 nTextHandle,���־��
                 nTextDataLength,�������ݳ���
                 pbyTextData,��������
                 bLocalOperate,�Ƿ��ն˷���Ĳ���
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnTextEditTextData( NodeID nInitiator ,
                                    s32 nTextHandle ,
                                    s32 nTextDataLength ,
                                    const u8* pbyTextData ,
                                    bool bLocalOperate ) = 0;

    /*====================================================================
    ������      :OnTextEditingTextStyle
    ����        :���ָ�ʽ�ı�֪ͨ���༭״̬�У�
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,����������ն˰װ�Ӧ��ID
                 nTextHandle,���־��
                 tTextColor,������ɫ
                 tLogfont,��������ṹ
                 nTextDataLength,�������ݳ���
                 pbyTextData,��������
                 bLocalOperate,�Ƿ��ն˷���Ĳ���
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnTextEditingTextStyle( NodeID nInitiator ,
                                        s32 nTextHandle ,
                                        const TStillImageColorRGB& tTextColor ,
                                        const TStillImageLogfont& tLogfont ,
                                        s32 nTextDataLength ,
                                        const u8* pbyTextData ,
                                        bool bLocalOperate ) = 0;

    /*====================================================================
    ������      :OnTextEditingTextColor
    ����        :������ɫ�ı�֪ͨ���༭״̬�У�
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,����������ն˰װ�Ӧ��ID
                 nTextHandle,���־��
                 tTextColor,������ɫ
                 nTextDataLength,�������ݳ���
                 pbyTextData,��������
                 bLocalOperate,�Ƿ��ն˷���Ĳ���
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnTextEditingTextColor( NodeID nInitiator ,
                                        s32 nTextHandle ,
                                        const TStillImageColorRGB& tTextColor ,
                                        s32 nTextDataLength ,
                                        const u8* pbyTextData ,
                                        bool bLocalOperate ) = 0;

    /*====================================================================
    ������      :OnTextEditTextStyle
    ����        :���ָ�ʽ�ı�֪ͨ���Ǳ༭״̬��
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,����������ն˰װ�Ӧ��ID
                 nTextHandle,���־��
                 tTextColor,������ɫ
                 tLogfont,�������壨����ṹ������ȫ0����ʱ��ʾ����ṹ��Ч������ɫ��Ч��
                 bLocalOperate,�Ƿ��ն˷���Ĳ���
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnTextEditTextStyle( NodeID nInitiator ,
                                     s32 nTextHandle ,
                                     const TStillImageColorRGB& tTextColor ,
                                     const TStillImageLogfont& tLogfont ,
                                     bool bLocalOperate ) = 0;

    /*====================================================================
    ������      :OnTextEditTextColor
    ����        :������ɫ�ı�֪ͨ���Ǳ༭״̬��
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,����������ն˰װ�Ӧ��ID
                 nTextHandle,���־��
                 tTextColor,������ɫ
                 tLogfont,��������
                 bLocalOperate,�Ƿ��ն˷���Ĳ���
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnTextEditTextColor( NodeID nInitiator ,
                                      s32 nTextHandle ,
                                      const TStillImageColorRGB& tTextColor ,
                                      bool bLocalOperate ) = 0;

    /*====================================================================
    ������      :OnTextEditViewState
    ����        :������ͼ״̬�仯֪ͨ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,����������ն˰װ�Ӧ��ID
                 nTextHandle,���־��
                 enumViewState,��ͼ״̬
                 bLocalOperate,�Ƿ��ն˷���Ĳ���
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnTextEditViewState( NodeID nInitiator ,
                                      s32 nTextHandle ,
                                      TStillImageText::ViewState enumViewState ,
                                      bool bLocalOperate ) = 0;

    /*====================================================================
    ������      :OnTextEditZOrder
    ����        :����Z�����λ�ñ仯֪ͨ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,����������ն˰װ�Ӧ��ID
                 nTextHandle,���־��
                 enumZOrder,Z�����λ��
                 bLocalOperate,�Ƿ��ն˷���Ĳ���
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnTextEditZOrder( NodeID nInitiator ,
                                   s32 nTextHandle ,
                                   TStillImageText::ZOrder enumZOrder ,
                                   bool bLocalOperate ) = 0;

    /*====================================================================
    ������      :OnTextEditAnchorPoint
    ����        :�����ƶ�֪ͨ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,����������ն˰װ�Ӧ��ID
                 nTextHandle,���־��
                 tAnchorPoint,���ֻ���
                 bLocalOperate,�Ƿ��ն˷���Ĳ���
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnTextEditAnchorPoint( NodeID nInitiator ,
                                        s32 nTextHandle ,
                                        const TStillImagePoint& tAnchorPoint ,
                                        bool bLocalOperate ) = 0;
///////////////////////////////////////////////////////////////////////
// �ļ�����Ӧ�� -- ���нӿں���
///////////////////////////////////////////////////////////////////////  

    /*====================================================================
    ������      :StartMBFT
    ����        :�����������ļ�����Ӧ��
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:��
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool StartMBFT( );

    /*====================================================================
    ������      :StopMBFT
    ����        :������ֹͣ�ļ�����Ӧ��
    �㷨ʵ��    :��
    ����ȫ�ֱ���:
                 
    �������˵��:��
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool StopMBFT( );

    /*====================================================================
    ������      :ResponseToReceiveFile
    ����        :ͬ��/�ܾ����ձ��ն��ļ�
    �㷨ʵ��    :��
    ����ȫ�ֱ���:
                 
    �������˵��:nInitiator,�����ļ����ն�ID
                 bConfirm,�Ƿ�ͬ������ļ�
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool ResponseToReceiveFile( NodeID nInitiator ,
                                bool bConfirm = true );

    /*====================================================================
    ������      :AcceptFile
    ����        :�ܹ�/���ܹ����ձ��ն��ļ�
    �㷨ʵ��    :��
    ����ȫ�ֱ���:
                 
    �������˵��:nInitiator,�����ļ����ն�ID
                 bConfirm,�Ƿ��ܹ������ļ�
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool AcceptFile( NodeID nInitiator ,
                     bool bConfirm = true );

    /*====================================================================
    ������      :RejectFile
    ����        :��;ֹͣ���ձ��ն˴�����ļ�
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��                 
    �������˵��:nInitiator,�����ļ����ն�ID
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool RejectFile( NodeID nInitiator );

    /*====================================================================
    ������      :InviteToReceiveFile
    ����        :������ն˽����ļ�
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:pnMBFTUserIds,��������ļ����ն�ID
                 nMBFTUserIds,��������ļ����ն�����
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool InviteToReceiveFile( NodeID* pnMBFTUserIds ,
                              s32 nMBFTUserIds );

    /*====================================================================
    ������      :OfferFile
    ����        :�ṩ�ļ���ʽ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��                 
    �������˵��:pchFileName,�ļ���
                 tTimeOfLastModification,����ļ��޸�ʱ��
                 nFileSize,�ļ�����
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool OfferFile( const char* pchFileName ,
                    const PTime& tTimeOfLastModification ,
                    s32 nFileSize );

    /*====================================================================
    ������      :StartTransferFile
    ����        :��ʼ�����ļ�
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:pchFileName,�ļ���
                 tTimeOfLastModification,����ļ��޸�ʱ��
                 nFileSize,�ļ�����
                 bFileEnd,�ļ������Ƿ����
                 nFileDataLength,���δ����ļ�����
                 pbyFileData,���δ����ļ�����
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool StartTransferFile( const char* pchFileName ,
                            const PTime& tTimeOfLastModification ,
                            s32 nFileSize ,
                            bool bFileEnd ,
                            s32 nFileDataLength ,
                            u8* pbyFileData );

    /*====================================================================
    ������      :TransferFileContinue
    ����        :���������ļ�
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:bFileEnd,�ļ������Ƿ����
                 nFileDataLength,���δ����ļ�����
                 pbyFileData,���δ����ļ�����
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool TransferFileContinue( bool bFileEnd ,
                               s32 nFileDataLength ,
                               u8* pbyFileData );

    /*====================================================================
    ������      :StopTransferFile
    ����        :��;ֹͣ�����ļ�
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:��
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool StopTransferFile();

    /*====================================================================
    ������      :SetMbftTimeOut
    ����        :���ô����ļ�����ĳ�ʱʱ��
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:dwTimeOut:��ʱʱ�䣨���룩
                 �������1000�����򷵻�ʧ��
                 Ĭ�ϳ�ʱʱ��Ϊ30��
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool SetMbftTimeOut(DWORD dwTimeOut);
/////////////////////////////////////////////////////////////////////////////////////
// �ļ�����Ӧ��  -- ������Ӧ����
/////////////////////////////////////////////////////////////////////////////////////

    /*====================================================================
    ������      :OnMBFTCapabilityNegotiationSuccess
    ����        :�����������ɹ�֪ͨ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:pnMBFTUserIds,���Է����ļ����ն�ID(�������ն�)
                 nMBFTUserNum,���Է����ļ����ն�����
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnMBFTCapabilityNegotiationSuccess( NodeID *pnMBFTUserIds ,
                                                     s32 nMBFTUserNum ) = 0;

    /*====================================================================
    ������      :OnInviteToReceiveFile
    ����        :���ն���������ļ�
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,�����ļ����ն�ID
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnInviteToReceiveFile( NodeID nInitiator ) = 0;

    /*====================================================================
    ������      :OnOfferFile
    ����        :���ն��ṩ�ļ���ʽ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,�����ļ����ն�ID
                 strFileName,�ļ���
                 tTimeOfLastModification,����ļ��޸�ʱ��
                 nFileSize,�ļ�����
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnOfferFile( NodeID nInitiator ,
                              const PString& strFileName ,
                              const PTime& tTimeOfLastModification ,
                              s32 nFileSize ) = 0;

    /*====================================================================
    ������      :OnStartTransferFile
    ����        :���ն˿�ʼ�����ļ�
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,�����ļ����ն�ID
                 strFileName,�ļ���
                 tTimeOfLastModification,����ļ��޸�ʱ��
                 nFileSize,�ļ�����
                 bFileEnd,�����ļ��Ƿ����
                 nFileDataLength,���δ������ݳ���
                 pbyFileData,����������
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnStartTransferFile( NodeID nInitiator ,
                                      const PString& strFileName ,
                                      const PTime& tTimeLastModification ,
                                      s32 nFileSize ,
                                      bool bFileEnd ,
                                      s32 nFileDataLength ,
                                      u8* pbyFileData ) = 0;

    /*====================================================================
    ������      :OnTransferFileContinue
    ����        :���ն˼��������ļ�
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,�����ļ����ն�ID
                 bFileEnd,�����ļ��Ƿ����
                 nFileDataLength,���δ������ݳ���
                 pbyFileData,����������
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnTransferFileContinue( NodeID nInitiator ,
                                        bool bFileEnd ,
                                        s32 nFileDataLength ,
                                        u8* pbyFileData ) = 0;

    /*====================================================================
    ������      :OnStopTransferFile
    ����        :���ն���;ֹͣ�����ļ�
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,�����ļ����ն�ID
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnStopTransferFile( NodeID nInitiator ) = 0;

    /*====================================================================
    ������      :OnResponseToReceiveFile
    ����        :���յ�����������ļ��ն˵Ļظ�
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nResponseUserNum,��ǰ�����ļ����ն�����(Ϊ0��ʾ�����ն˽���)
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnResponseToReceiveFile( s32 nResponseUserNum ) = 0;

    /*====================================================================
    ������      :OnAcceptFile
    ����        :���ն��ļ���ʽ�ظ�
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nAcceptFileUserNum,��ǰ�����ļ����ն�����(Ϊ0��ʾ�����ն˽���)
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnAcceptFile( s32 nAcceptFileUserNum ) = 0;

    /*====================================================================
    ������      :OnRejectFile
    ����        :�����ļ���;�ն�ֹͣ�����ļ�
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nReceivingFileUserNum,��ǰ�����ļ����ն�����(Ϊ0��ʾ�����ն˽���)
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnRejectFile( s32 nReceivingFileUserNum ) = 0;

    /*====================================================================
    ������      :OnTransferFileEnd
    ����        :�����ļ����
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:��
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnTransferFileEnd() = 0;

///////////////////////////////////////////////////////////////////////
// ����Ӧ��  -- ���нӿں���
///////////////////////////////////////////////////////////////////////  
 
    /*====================================================================
    ������      :StartChat
    ����        :��������������Ӧ��
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:��
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool StartChat( );

    /*====================================================================
    ������      :StopChat
    ����        :������ֹͣ����Ӧ��
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:��
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool StopChat( );

    /*====================================================================
    ������      :SendText
    ����        :���͹�����Ϣ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nTextLength,������Ϣ����
                 pbyText,������Ϣ����
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool SendText( s32 nTextLength , u8* pbyText );

    /*====================================================================
    ������      :SendPrivateText
    ����        :����˽����Ϣ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nPrivateUserId,Ŀ���ն�ID
                 nTextLength,������Ϣ����
                 pbyText,������Ϣ����
    ����ֵ˵��  :true : ����ִ�гɹ�
                 false: ����ִ��ʧ��
    ====================================================================*/
    bool SendPrivateText( NodeID nPrivateUserId ,
                          s32 nTextLength ,
                          u8* pbyText );

/////////////////////////////////////////////////////////////////////////////////////
// ����Ӧ��  -- ������Ӧ����
/////////////////////////////////////////////////////////////////////////////////////

    /*====================================================================
    ������      :OnChatCapabilityNegotiationSuccess
    ����        :�����������ɹ�֪ͨ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:pnChatUserIds,����������ն�ID(�������ն�)
                 nChatUserNum,����������ն�����
    ����ֵ˵��  :��
    ====================================================================*/
    virtual void OnChatCapabilityNegotiationSuccess( NodeID *pnChatUserIds ,
                                                    s32 nChatUserNum ) = 0;

    /*====================================================================
    ������      :OnReceivedText
    ����        :���յ�������Ϣ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,����������Ϣ���ն�ID
                 nTextLength,������Ϣ����
                 pbyText,������Ϣ����
    ����ֵ˵��  :��
    ====================================================================*/
	virtual void OnReceivedText( NodeID nInitiator ,
                                 s32 nTextLength ,
                                 u8* pbyText ) = 0;

    /*====================================================================
    ������      :OnReceivedPrivateText
    ����        :���յ�˽����Ϣ
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:nInitiator,����������Ϣ���ն�ID
                 nTextLength,������Ϣ����
                 pbyText,������Ϣ����
    ����ֵ˵��  :��
    ====================================================================*/
	virtual void OnReceivedPrivateText( NodeID nInitiator ,
                                        s32 nTextLength ,
                                        u8* pbyText ) = 0;


///////////////////////////////////////////////////////////////////////
// ���Բ�ѯ  -- ���Դ�ӡ�ڲ���Ϣ
///////////////////////////////////////////////////////////////////////  
 
    /*====================================================================
    ������      :PrintStatus
    ����        :��ӡ��ǰDcMtLib��״̬
    �㷨ʵ��    :��
    ����ȫ�ֱ���:��
    �������˵��:��
    ����ֵ˵��  :��
    ====================================================================*/
    bool PrintStatus();
};

#endif//_DCMTADAPTER_H