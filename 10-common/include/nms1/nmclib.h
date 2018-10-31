/********************************************************************
	ģ����:      NMClib
	�ļ���:      nmclib.h
	����ļ�:    
	�ļ�ʵ�ֹ��� ���ܿͻ��˽ӿ�������
    ���ߣ�       ������
	�汾��       3.5
------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��		�汾		�޸���		�߶���    �޸�����
	2004/08/02	3.5			������                  ����

*********************************************************************/

#pragma once

#include "nmsmacro.h"
#include "NMCLibDef.h"
#include <vector>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// �ӿڶ���
class INMCNotifyWnd
{
protected:
    HWND m_hNotifyWnd;
    void Post2Application(u32 uMsgType, WPARAM wParam = 0, LPARAM lParam = 0);
    void Send2Application(u32 uMsgType, WPARAM wParam = 0, LPARAM lParam = 0);

public:
    INMCNotifyWnd() {m_hNotifyWnd = NULL;};
	/*����	��ȡ֪ͨ��ϢĿ�Ĵ���
	����	��
	����ֵ	��ϢĿ�Ĵ���
	˵��	��*/
    HWND GetNotifyWnd() {return m_hNotifyWnd;};
	/*����	����֪ͨ��ϢĿ�Ĵ���
	����	hWnd	��ϢĿ�Ĵ���
	����ֵ	��
	˵��	��*/
    void SetNotifyWnd(HWND hWnd) {m_hNotifyWnd = hWnd;};

};

class INMCDevice 
{
public:
    //ͬ��
    virtual u32 SyncCfg() = 0;
    virtual u32 SyncTime() = 0;
    virtual u32 SyncAlarm() = 0;    

    /*=============================================================================
    �� �� ���� RemoteControl
    ��    �ܣ� Զ�̿���
    ��    ���� u8 byCmdType :��������
               PTBoard pBoard = NULL������
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 RemoteControl(u8 byCmdType, PTBoard pBoard = NULL) = 0;

    /*=============================================================================
    �� �� ���� QueryMockMachine
    ��    �ܣ� ��ѯ�豸���ܹ�������
    ��    ���� u32 dwDeviceID��[in]�豸ID
               TMockMachineData& tMockData: [out]���ܽṹ��Ϣ
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 QueryMockMachine(TMockMachineData& tMockData) = 0;
	virtual u32 QuerySonDevice( u32 dwDeviceID, vector<INMCDevice*>& vecpDevice) = 0;
    /*=============================================================================
    �� �� ���� MockBoardRefresh
    ��    �ܣ� ������Ϣˢ��
    ��    ���� TBoard& tBoard: [in]������Ϣ
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 MockBoardRefresh(const TBoard &tBoard) = 0;

    /*=============================================================================
    �� �� ���� FtpUpload
    ��    �ܣ� �ļ��ϴ�
    ��    ���� LPCTSTR lpszRemoteFile���ļ����豸�е�����
               LPCTSTR lpszFilePath�������ļ�·�����ļ���
               u8 byOsType������ϵͳ����
               PTBoard pBoard = NULL������
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 FtpUpload(LPCTSTR lpszRemoteFile, LPCTSTR lpszFilePath, 
                          u8 byOsType, PTBoard pBoard = NULL) = 0;

    /*=============================================================================
    �� �� ��:FtpFileRename
    ��    ��:�ϴ��ļ�������, ������
    ��    ��:vector<CString> vctRemoteFile  [in]    �ļ�ȫ��
             PTBoard ptBoard                [in]    ����
    ע    ��:��
    �� �� ֵ:�ɹ�: 0; ʧ��: ������ 
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/03/29  4.0     ���    ����
    =============================================================================*/
    virtual u32 FtpFileRename(vector<CString> vctRemoteFile, PTBoard ptBoard = NULL) = 0;

    /*=============================================================================
    �� �� ���� FtpDownload
    ��    �ܣ� �ļ�����
    ��    ���� LPCTSTR lpszRemoteFile���ļ����豸�е�����
               LPCTSTR lpszFilePath�������ļ�·�����ļ���
               u8 byOsType������ϵͳ����
               PTBoard pBoard = NULL������
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 FtpDownload(LPCTSTR lpszRemoteFile, LPCTSTR lpszFilePath,
                            u8 byOsType, PTBoard pBoard = NULL) = 0;    

    // �����豸�ı���
    virtual u32 RenameAlias(LPCTSTR lpszAlias) = 0;

    virtual void SetPrivilege(u32 dwPrivilege) = 0;


    /*=============================================================================
    �� �� ���� 
    ��    �ܣ� �������úͲ���(MCU)
    ��    ���� TBoard& tBoard:������Ϣ
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 BoardReset(const TBoard& tBoard) = 0;
    virtual u32 BoardSyncTime(const TBoard& tBoard) = 0;
    virtual u32 BoardBitErrTest(const TBoard& tBoard) = 0;
    virtual u32 BoardSelfTest(const TBoard& tBoard) = 0;
    virtual u32 DSIBoardE1Cfg(const TDSIBoard& tBoard) = 0;

    //////////////////////////////////////////////////////////////////////////
    //����
    virtual void ShowCurrentAlarm() = 0;
    
    //////////////////////////////////////////////////////////////////////////
    //����
    virtual u32 GetDeviceID() = 0;
	virtual u32 GetDevicePID() = 0;
    virtual u16 GetDeviceType() = 0;
    virtual u8  GetTopAlarmLevel() = 0;
    virtual u32 GetPrivilege() = 0;
    virtual u32 GetDevicePos(u32& xPos, u32& yPos) = 0;
	virtual BOOL32 GetIpAddr(u32& dwIpAddr) = 0;
	virtual BOOL32 GetIpAddr(LPTSTR lpsIpAddr) = 0;
    virtual LPCTSTR GetAlias() = 0;
    virtual u8 GetLinkStatus() = 0;
    virtual LPCTSTR GetAlarmDesc() = 0;
    virtual LPCTSTR GetHardVer(void) const = 0; //  ��ȡӲ���汾��
    virtual LPCTSTR GetSoftVer(void) const = 0; //  ��ȡ����汾��

    /*=============================================================================
    �� �� ��:GetOsType
    ��    ��:��ȡ����ϵͳ����
    ��    ��:��
    ע    ��:��
    �� �� ֵ:����ϵͳ����
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/08/14  4.0     ���    ����
    =============================================================================*/
    virtual u8 GetOsType(void) const = 0;
};


class INMCDeviceDir
{
public:
    /*=============================================================================
    �� �� ���� ReNameDir
    ��    �ܣ� �޸��豸Ŀ¼����
    ��    ���� LPCTSTR lpszNewName����Ŀ¼��
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 ReNameDir(LPCTSTR lpszNewName) = 0;

    /*=============================================================================
    �� �� ���� MoveDir
    ��    �ܣ� �ƶ��豸Ŀ¼
    ��    ���� u32 dwSuperID��Ŀ��Ŀ¼ID���ƶ���ĸ�Ŀ¼
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 MoveDir(u32 dwSuperID) = 0;

    /*=============================================================================
    �� �� ���� DirMemberAdd
    ��    �ܣ� ������Ŀ¼��Ա
    ��    ���� u32 dwDirID�����ӵ��豸ID
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 DirMemberAdd(u32 dwDirID) = 0;

    /*=============================================================================
    �� �� ���� DeleteDirMember
    ��    �ܣ� ɾ����Ŀ¼��Ա
    ��    ���� u32 dwDirID��ɾ�����豸ID
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 DeleteDirMember(u32 dwDirID) = 0;

    /*=============================================================================
    �� �� ���� AppendDevice
    ��    �ܣ� �����豸��Ա��ֻ�����б�
    ��    ���� u32 dwDeviceID�����ӵ��豸ID
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 AppendDevice(u32 dwDeviceID) = 0;

    /*=============================================================================
    �� �� ���� DeleteDirMember
    ��    �ܣ� ɾ���豸��Ա��ֻɾ���б�
    ��    ���� u32 dwDeviceID��ɾ�����豸ID
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 DeleteDeviceMember(u32 dwDeviceID) = 0;

    /*=============================================================================
    �� �� ���� SetDirMemberPos
    ��    �ܣ� �趨��Ա�豸��λ��
    ��    ���� u32 dwDeviceID:�豸ID
               u32 dwPosX:�豸λ��ˮƽ����
               u32 dwPosY:�豸λ�ô�ֱ����
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 SetDirMemberPos(u32 dwDeviceID, u32 dwPosX, u32 dwPosY) = 0;
    virtual u32 GetDirMemberPos(u32 dwDeviceID, u32& dwPosX, u32& dwPosY) = 0;

    virtual u32 GetDirPos(u32& dwPosX, u32& dwPosY) = 0;
    virtual u32 SetDirPos(u32 dwPosX, u32 dwPosY) = 0;

    virtual u32 GetChildDir(vector<u32>& vecDirID) = 0;
    virtual u32 GetChildDir(vector<INMCDeviceDir*>& vecpDir) = 0;
    virtual u32 GetChildDevice(vector<u32>& vecDeviceID) = 0;
    virtual u32 GetChildDevice(vector<INMCDevice*>& vecpDevice) = 0;
    virtual INMCDeviceDir* GetSuperDir() = 0;
    virtual u32 GetDirID() = 0;
    virtual BOOL32 HasSubDeviceDir() = 0;
    virtual BOOL32 HasDeviceMember() = 0;
    virtual BOOL32 IsMemberExists(u32 dwDeviceID) = 0;
    virtual u8  GetTopAlarmLevel() = 0;
    virtual LPCTSTR GetDirName() = 0;

};

class INMCUser
{
public:
    /*=============================================================================
    �� �� ���� ModifyUser
    ��    �ܣ� �޸��û���Ϣ
    ��    ���� const TUserBaseInfo& tUserInfo: [in]��������û���Ϣ��
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 ModifyUser(const TUserBaseInfo& tUserInfo) = 0;
    
    /*=============================================================================
    �� �� ���� QueryGroupsOfUser
    ��    �ܣ� ��ѯ�û����ڵ����е��顣
    ��    ���� u32 dwUserID:�û�ID
               vector<PTNameInfo>& vecNameInfo��[out]�����û����ڵ������Ϣ
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 QueryGroupsOfUser(vector<PTNameInfo>& vecNameInfo) = 0;

    /*=============================================================================
    �� �� ���� LinkGroup
    ��    �ܣ� ���루�˳����û���
    ��    ���� u32 dwGroupID��Ŀ���û���
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 LinkGroup(u32 dwGroupID) = 0;
    virtual u32 UnLinkGroup(u32 dwGroupID) = 0;
    
    /*=============================================================================
    �� �� ���� GetUserPrivilege
    ��    �ܣ� ��ѯ�û�Ȩ��
    ��    ���� vector<TPrivilege>& vecPrivilege��[out]Ȩ����Ϣ
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 GetUserPrivilege(vector<TPrivilege>& vecPrivilege) = 0;
    virtual u32 StatPrivilege() = 0;

    //////////////////////////////////////////////////////////////////////////
    //����
    virtual u32 GetUserID() = 0;
    virtual LPCTSTR GetLogonName() = 0;
    virtual u32 GetInformation(TUserBaseInfo& tInfo) = 0;
    virtual u32 FindPrivilege(u32 dwDeviceID, u32& dwPrivilege) = 0;
    virtual BOOL32 IsAdministrator() = 0;
    virtual BOOL32 IsExistGroup(u32 dwGroupID) = 0;
};

class INMCGroup
{
public:    
    /*=============================================================================
    �� �� ���� ModifyGroupInfo
    ��    �ܣ� �޸��û�����Ϣ
    ��    ���� const TGroupBaseInfo& tGroupBaseInfo:[in]�û�����Ϣ
    �� �� ֵ�� u32:�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 ModifyGroupInfo(const TGroupBaseInfo& tGroupBaseInfo) = 0;

    virtual u32 GetGroupID() = 0;
    virtual u32 GetGroupBaseInfo(TGroupBaseInfo& tGroupBaseInfo) = 0;
    
    /*=============================================================================
    �� �� ���� SetPrivilege
    ��    �ܣ� ���ã��õ����û���Ȩ��
    ��    ���� const TPrivilege& tPrivilege��[in]Ȩ����Ϣ
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 SetPrivilege(const TPrivilege& tPrivilege) = 0;
    virtual u32 GetPrivilege(TPrivilege& tPrivilege) = 0;

    /*=============================================================================
    �� �� ���� AddUser
    ��    �ܣ� �û����루�˳����û���
    ��    ���� u32 dwUserID:�û�ID
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 AddUser(u32 dwUserID) = 0;
    virtual u32 DeleteUser(u32 dwUserID) = 0;
    
    /*=============================================================================
    �� �� ���� QueryGroupPrivilege
    ��    �ܣ� ��ѯ�û���Ȩ��
    ��    ���� vector<TPrivilege>& vecPrivilege��[out]Ȩ����Ϣ
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 QueryGroupPrivilege(vector<TPrivilege>& vecPrivilege) = 0;
    
    /*=============================================================================
    �� �� ���� QueryUsersInGroup
    ��    �ܣ� ��ѯ�û����е����е��û�
    ��    ���� vector<PTNameInfo>& vecNameInfo��[out]���������е��û�����Ϣ
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 QueryUsersInGroup(vector<PTNameInfo>& vecNameInfo) = 0;

    //////////////////////////////////////////////////////////////////////////
    //
    virtual BOOL32 IsExistUser(u32 dwUserID) = 0;
};

 
//ϵͳ����ӿڣ��û�����
class ISysManager : public INMCNotifyWnd
{
public:
    virtual INMCUser* GetUser(u32 dwUserID) = 0;
    virtual INMCGroup* GetGroup(u32 dwGroupID) = 0;

    /*=============================================================================
    �� �� ���� AddUser
    ��    �ܣ� �����û�
    ��    ���� TUserBaseInfo& tUserInfo: [in\out]��������û���Ϣ,����ID��
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 AddUser(TUserBaseInfo& tUserInfo) = 0;

    /*=============================================================================
    �� �� ���� DeleteUser
    ��    �ܣ� ɾ���û�
    ��    ���� u32 dwUserID: [in]ɾ�����û�ID��
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 DeleteUser(u32 dwUserID) = 0;


    /*=============================================================================
    �� �� ���� EnumUsers
    ��    �ܣ� �õ����е��û���Ϣ
    ��    ���� vector<PTNameInfo>& vecUserInfo:
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 EnumUsers(vector<PTNameInfo>& vecUserInfo) = 0;


    /*=============================================================================
    �� �� ���� CreateGroup
    ��    �ܣ� �����û���
    ��    ���� TGroupBaseInfo& tGroupBaseInfo: [in\out]��������û�����Ϣ,����ID��
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 CreateGroup(TGroupBaseInfo& tGroupBaseInfo) = 0;


    /*=============================================================================
    �� �� ���� DestroyGroup
    ��    �ܣ� �����û���
    ��    ���� u32 dwGroupID���û���ID
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 DestroyGroup(u32 dwGroupID) = 0;

    /*=============================================================================
    �� �� ���� EnumGroups
    ��    �ܣ� �õ����е��û���
    ��    ���� vector<PTNameInfo>& vecGroupInfo:[out]���е��û������Ϣ
    �� �� ֵ�� u32:�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 EnumGroups(vector<PTNameInfo>& vecGroupInfo) = 0;  

    /*=============================================================================
    �� �� ���� ChangePWD
    ��    �ܣ� �޸ĵ�ǰ�û�����
    ��    ���� LPCTSTR lpszOldPSW��������
               LPCTSTR lpszNewPSW��������
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 ChangePWD(LPCTSTR lpszOldPSW, LPCTSTR lpszNewPSW) = 0;


    /*=============================================================================
    �� �� ���� QueryOprLog
    ��    �ܣ� ��ѯ��ɾ������־
    ��    ���� const TOprLogCondition& tCondition: [in]��ѯ����
               u32& dwRecCount: [out]��ѯ�����Ŀ
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 QueryOprLog(const TOprLogCondition& tCondition, u32& dwRecCount) = 0;
    virtual u32 DelOprLog(const TOprLogCondition& tCondition) = 0;
    virtual u32 DelOprLog(u32 dwSerial) = 0;
    
    /*=============================================================================
    �� �� ���� GetNextBatchRecord
    ��    �ܣ� ��ȡ��һ����¼
    ��    ���� u32& dwRemainCount:         [out]��ʣ�µļ�¼����
               PTOprLogResult pContent:    [out/buffer] ��¼�б��ڴ�
               u32 dwRecCount:             [in] ��¼�ڴ��п��Ա����������¼
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 GetNextBatchRecord(u32& dwRemainCount, PTOprLogResult pContent,
        u32& dwRecCount) = 0;
};

//�澯��Ϣ�ӿ�
class IAlarmInfo : public INMCNotifyWnd
{
public:
    //////////////////////////////////////////////////////////////////////////
    //�澯֪ʶ��

    /*=============================================================================
    �� �� ���� GetAlarmKBInfo
    ��    �ܣ� ��ѯ�澯֪ʶ�⣬ĳ���澯�Ļ�����Ϣ��
    ��    ���� u32 dwAlarmCode: [in]������
               vector<PTAlarmKBInfo>& vecKBInfo��[out]֪ʶ�����ݣ����ܲ�ֻһ����
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 GetAlarmKBInfo(u32 dwAlarmCode, vector<PTAlarmKBInfo>& vecKBInfo) = 0;
    
    /*=============================================================================
    �� �� ���� GetAlarmKBCause
    ��    �ܣ� ��ѯ�澯֪ʶ�⣬ĳ���澯ԭ��
    ��    ���� u32 dwAlarmCode: [in]������
               vector<PTAlarmKBCause>& vecKBCause��[out]ԭ�����ݣ����ܲ�ֻһ����
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 GetAlarmKBCause(u32 dwAlarmCode, vector<PTAlarmKBCause>& vecKBCause) = 0;
    
    /*=============================================================================
    �� �� ���� GetAlarmKBSolution
    ��    �ܣ� ��ѯ�澯֪ʶ�⣬ĳ���������
    ��    ���� u32 dwAlarmCode: [in]������
               vector<PTAlarmKBCause>& vecKBSolution��[out]������������ܲ�ֻһ����
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 GetAlarmKBSolution(u32 dwAlarmCode, vector<PTAlarmKBCause>& vecKBSolution) = 0;


    /*=============================================================================
    �� �� ���� InsertAlarmKBInfo etc.
    ��    �ܣ� ���Ӹ澯֪ʶ�������Ϣ;�޸�;ɾ��
    ��    ���� TAlarmKBInfo tAlarmKBInfo: [in]�澯��Ϣ
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 InsertAlarmKBInfo(const TAlarmKBInfo& tAlarmKBInfo) = 0;
    virtual u32 ModifyAlarmKBInfo(const TAlarmKBInfo& tAlarmKBInfo) = 0;
    virtual u32 DeleteAlarmKBInfo(u32 dwAlarmCode) = 0;

    /*=============================================================================
    �� �� ���� InsertAlarmKBInfo etc.
    ��    �ܣ� ���Ӹ澯֪ʶ��澯ԭ��;�޸�;ɾ��
    ��    ���� TAlarmKBCause& tAlarmKBCause: [in]�澯ԭ��
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 InsertAlarmKBCause(const TAlarmKBCause& tAlarmKBCause) = 0;
    virtual u32 ModifyAlarmKBCause(const TAlarmKBCause& tAlarmKBCause) = 0;
    virtual u32 DeleteAlarmKBCause(u32 dwAlarmCode) = 0;

    /*=============================================================================
    �� �� ���� InsertAlarmKBSolution etc.
    ��    �ܣ� ���Ӹ澯֪ʶ��澯�������;�޸�;ɾ��
    ��    ���� TAlarmKBCause& tAlarmKBSolution: [in]�澯�������
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 InsertAlarmKBSolution(const TAlarmKBCause& tAlarmKBSolution) = 0;
    virtual u32 ModifyAlarmKBSolution(const TAlarmKBCause& tAlarmKBSolution) = 0;
    virtual u32 DeleteAlarmKBSolution(u32 dwAlarmCode) = 0;

    //////////////////////////////////////////////////////////////////////////
    //�澯

    /*=============================================================================
    �� �� ���� QueryCurrentAlarm
    ��    �ܣ� ��ѯ�豸�ĵ�ǰ�澯
    ��    ���� const u32 dwDeviceID��       [in]�豸ID����0Ϊ���е��豸��
               u32& dwRecCount��            [out]�õ��ĸ澯��Ŀ
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 QueryCurrentAlarm(const u32 dwDeviceID, u32& dwRecCount) = 0;

    /*=============================================================================
    �� �� ���� QueryHistoryAlarm etc.
    ��    �ܣ� ��ѯ��ʷ�澯;ɾ��
    ��    ���� const THistoryAlarmCondition& tHAlarmCond: [in]��ѯ����
               u32& dwRecCount��            [out]�õ��ĸ澯��Ŀ
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 QueryHistoryAlarm(const THistoryAlarmCondition& tHAlarmCond,
        u32& dwRecCount) = 0;
    virtual u32 DeleteHistoryAlarm(const THistoryAlarmCondition& tHAlarmCond) = 0;
    virtual u32 DeleteHistoryAlarm(u32 dwSerial) = 0;


    /*=============================================================================
    �� �� ���� GetNextBatchRecord
    ��    �ܣ� ��ȡ��һ����¼
    ��    ���� u32 dwRemainCount:          [out]��ʣ�µļ�¼����
               PTAlarmContent pContent:    [out/buffer] ��¼�б��ڴ�
               u32 dwRecCount:             [in/out] ��¼�ڴ��п��Ա����������¼
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 GetNextBatchRecord(u32& dwRemainCount, PTAlarmContent pContent,
        u32& dwRecCount) = 0;
    //////////////////////////////////////////////////////////////////////////
    //�澯����

    /*=============================================================================
    �� �� ���� SetAlarmFilter
    ��    �ܣ� ���ø澯����
    ��    ���� const TAlarmFilter& tAlarmFilter:�澯��������
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 SetAlarmFilter(const TAlarmFilter& tAlarmFilter) = 0;

    /*=============================================================================
    �� �� ���� QueryAlarmCodeFilter etc.
    ��    �ܣ� ��ѯ�澯����������
    ��    ���� vector<u32>& vecAlarmFilter�� [out] �澯������������ѯ���
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 QueryAlarmCodeFilter(vector<u32>& vecCodeFilter) = 0;
    virtual u32 QueryAlarmLevelFilter(vector<u8>& vecLevelFilter) = 0;


    /*=============================================================================
    �� �� ���� DeleteAlarmCodeFilter
    ��    �ܣ� ɾ���澯��������
    ��    ���� 
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 DeleteAlarmCodeFilter() = 0;
    virtual u32 DeleteAlarmLevelFilter() = 0;

    virtual u32 GetAlarmRemark(u32 dwCode, LPTSTR lpRemark) = 0;
    virtual u32 GetAllAlarmRemark(vector<PTAlarmRemark>& vecAlarmRemark) = 0;
};

//�豸����ӿ�
class IDeviceManager : public INMCNotifyWnd
{
public:
    
    virtual INMCDevice* GetDevice(u32 dwDeviceID) = 0;
    virtual INMCDeviceDir* GetDeviceDir(u32 dwDirID) = 0;
    virtual INMCDeviceDir* GetRootDeviceDir() = 0;

    /*=============================================================================
    �� �� ���� FtpBreak
    ��    �ܣ� �ж��ļ�����
    ��    ���� 
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 FtpBreak() = 0;
    
    /*=============================================================================
    �� �� ���� AddDevice
    ��    �ܣ� ����һ���豸
    ��    ���� u32 dwIPAddr���豸IP��ַ
               u16 wDevieType���豸����
               LPCTSTR lpszAlias���豸����
               u32& dwDeviceID����out�����豸ID
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 AddDevice(u32 dwIPAddr, u16 wDevieType, LPCTSTR lpszAlias,
        u32& dwDeviceID, u32 dwDevicePID) = 0;
    

    /*=============================================================================
    �� �� ���� DeleteDevice
    ��    �ܣ� ɾ��һ���豸
    ��    ���� u32 dwDeviceID���豸ID
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 DeleteDevice(u32 dwDeviceID) = 0;

    /*=============================================================================
    �� �� ���� CreateDir
    ��    �ܣ� ����һ���豸Ŀ¼
    ��    ���� LPCTSTR lpszName��Ŀ¼��
               u32 dwSuperID���ϼ�Ŀ¼ID
               u32& dwDirID����out����Ŀ¼ID
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 CreateDir(LPCTSTR lpszName, u32 dwSuperID, u32& dwDirID) = 0;

    /*=============================================================================
    �� �� ���� DestroyDir
    ��    �ܣ� �����豸Ŀ¼
    ��    ���� u32 dwDirID��Ŀ¼ID
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    =============================================================================*/
    virtual u32 DestroyDir(u32 dwDirID) = 0;

    virtual u32 GetDeviceCount(u32& dwDeviceCount) = 0;
    virtual LPCTSTR GetFtpUser() = 0;
    virtual LPCTSTR GetFtpPwd() = 0;

    /*�������� ExConfQuery
    ��    �ܣ� 
    ��    ���� vector<PTConfRecord>& vecRecord
    �� �� ֵ�� u32 
    ˵    ���� */
    virtual u32 ExConfQuery(vector<PTConfRecord>& vecRecord) = 0;
    virtual u32 ExMtQuery(LPCTSTR lpConfID, vector<PTMtRecord>& vecRecord) = 0;
	virtual u32 EQPQuery(u32 dwDirID, vector<PTEquipProperty>& vecRecord) = 0;

    virtual u32 DelConfInfo(LPCSTR lpConfID = NULL) = 0;
};

class IConnectSever : public INMCNotifyWnd
{
public:
	/*����	��½������
	����	lpszUserName	�û���
			lpszPSW	����
			dwIP	�����ӷ�������IP��ַ��������
            dwPort  �������˿�
	����ֵ	�ɹ�����0,ʧ�ܷ��ط�0������
	˵��	������ʧ�ܣ�����*/
    virtual u32 LogonSever(LPCTSTR lpszUserName, LPCTSTR lpszPSW,
        u32 dwIP, u16 wPort = 2010) = 0;

	/*����	�Ͽ��������������
	����	��
	����ֵ	�ɹ�����0,ʧ�ܷ��ط�0������
	˵��	��û�����ӵ�������ʱ���ô˷����������κ�����*/
    virtual u32 LogoffSever() = 0;

	/*����	�ж��Ƿ��ѵ�½������
	����	��
	����ֵ	�ѵ�½����TRUE,���򷵻�FALSE
	˵��	��*/
    virtual BOOL32 IsLogonSever() = 0;


	/*����	��ȡ�ض��Ŀ��ƽӿ�
	����	ppCtrl	���ƽӿ�
	����ֵ	�ɹ�����0,ʧ�ܷ��ط�0������
	˵��	�����ӵ��ն�ʱ,���Ի�ȡ��Щ�ӿ�,�ڶϿ����Ӻ�,������Щ�ӿ�����ʧЧ*/
    virtual u32 NMCGetInterFace(ISysManager** ppCtrl) = 0;
    virtual u32 NMCGetInterFace(IAlarmInfo** ppCtrl) = 0;
    virtual u32 NMCGetInterFace(IDeviceManager** ppCtrl) = 0;

    // �㲥�������ܷ������ĵ�ַ
	virtual u32 BroadcastForSearchNms(vector<TNmsEnvData>& vecNmsData) = 0;

    //�õ���ǰ�û�ID
    virtual u32 GetCurrUserID(u32& dwUserID) = 0;
    virtual INMCUser* GetCurrUser() = 0;
    
    //  wanghao 2006/01/05 �����л�˫��ʱ���¶�����
    virtual u32 ConstructAffairData() = 0;
};

////////////////////////////////////////////////////////////////////////////////

class CNMCLib
{
public:
	/*����	����ʵ���˽ӿ�IConnectSever�Ķ���
	����	ppConnect	[out]�ɹ�����IConnectSever�ӿ�,ʧ�ܷ���NULL
	����ֵ	�ɹ�����0,ʧ�ܷ��ط�0������
	˵��	�ӿ�ʹ����ɺ�,����DestroyInstance�������ٶ���*/
    static u32 CreateInstance(IConnectSever** ppConnect);

	/*����	����ʵ���˽ӿ�ppConnect�Ķ���
	����	ppConnect	[in, out]�ӿ�IMtcConnectMt,�ɹ��󷵻�NULL
	����ֵ	�ɹ�����0,ʧ�ܷ��ط�0������
	˵��	ֻ��������CreateInstance���������Ķ���*/
	static u32 DestroyInstance(IConnectSever **ppConnect);

	/*����	��ʽ������
	����	dwError:	������
	����ֵ	������˵����
	˵��	*/
    static LPCTSTR FormatErrorMsg(u32 dwError);

    static LPCTSTR ConvertIpAddr(DWORD dwIpAddr);
    static BOOL32 SplitFileName(LPCTSTR lpszFilePath, LPTSTR lpsFileName);

    enum EMLanguage
    {
        emEnglish = 0,
        emChinese = 1
    };

public:
    static EMLanguage s_emLanguage;
};

/*=============================================================================
�� �� ��:nmclibhelp
��    ��:nmclib��ӡ����
��    ��:��
ע    ��:��
�� �� ֵ:��
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2006/04/05  4.0     ���    ����
=============================================================================*/
API void nmclibhelp(void);

/*=============================================================================
�� �� ��:nmclibver
��    ��:��ӡnmclib�汾
��    ��:��
ע    ��:��
�� �� ֵ:��
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2006/04/05  4.0     ���    ����
=============================================================================*/
API void nmclibver(void);
