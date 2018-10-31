/********************************************************************
ģ����:      ���ܿͻ��˽�����Կ�
�ļ���:      NmsClientIntTestUiEx.h
����ļ�:    NmcCom.h, GuiUnit.h, NMCLibDef.h
�ļ�ʵ�ֹ��� ���ܿͻ��˼��ɲ��Խ����ӿڶ���
���ߣ�       ������
�汾��       3.5
------------------------------------------------------------------------
�޸ļ�¼:
��  ��		�汾		�޸���		�߶���    �޸�����
2004/10/15	3.5			������                  ����
*********************************************************************/

/*********************************************************************
							ʹ��˵��

1.�ȵ��� GuiRunNmsClient(char* szPath) �ӿ�, �������ܿͻ���Ӧ�ó���·����,
  �˺������Զ�����Ӧ�ó����Ƿ��Ѿ����������

2.�ٵ��� SetGuiMainWindow(int nTimeOut = 0) �ӿ�, ���볬ʱֵ,
  ��Ϊ1.������Ӧ�ó�����ʽ������Ҫһ��ʱ��, ���ڴ�ʱ���ڳɹ�����������true,
  ���򷵻�false, �ⲿ��������ʱ����

3.�ٵ���ConnectNms(LPCTSTR szIp, DWORD dwPort, LPCTSTR szUser, LPCTSTR szPwd),
  �������Ӳ����������ܿͻ���

4.���ӿͻ��˳ɹ���,�ٵ���GuiInitUIHandle()�ӿڶԽ���Ԫ�ؽ��г�ʼ��, 
  ��3.������ʧ�ܽ����ʼ��ʧ��

5.�ٵ��� SetOprDelay(BOOL bDelay = TRUE) ���þ�������Ƿ���ʱ,Ĭ��Ϊ����ʱ

6.�����þ���ӿڽ��н������.
*********************************************************************/

#ifndef	__NMSCLIENTINTTESTUIEX_H
#define __NMSCLIENTINTTESTUIEX_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cppunit\cppunit\GuiUnit.h"
#include "NMCLibDef.h"
#include "NmcTestUiCom.h"

class CNmsClientIntTestUiEx
{
public:
	CNmsClientIntTestUiEx();
	virtual ~CNmsClientIntTestUiEx();

public:
    /*�������� ClearConfInfo
    ��    �ܣ� 
    ��    ���� 
    �� �� ֵ�� BOOL
    ˵    ���� */
    BOOL ClearConfInfo();
    
    /*�������� DeleteConfInfo
    ��    �ܣ� 
    ��    ���� LPCTSTR lpConfID
    �� �� ֵ�� 
    ˵    ���� BOOL*/
    BOOL DeleteConfInfo(LPCTSTR lpConfID);
/*=============================================================================
  �� �� ���� SingleBoardOp
  ��    �ܣ� ������� 
  ��    ���� 
  �� �� ֵ�� BOOL  
=============================================================================*/
    BOOL SingleBoardOp(const TSingleBoard& tBoard, int nOpType, BOOL bOK = TRUE);

/*=============================================================================
  �� �� ���� SingleBoardOp
  ��    �ܣ� �����ϴ������� 
  ��    ���� 
  �� �� ֵ�� BOOL  
=============================================================================*/
    BOOL SingleBoarUpLoad(const TSingleBoard& tBoard, CString strFileName, BOOL bOK = TRUE);
    BOOL SingleBoarDownLoad(const TSingleBoard& tBoard, CString strFileName, BOOL bOK = TRUE);

	BOOL CloseWindow();
/*=============================================================================
  �� �� ���� GuiRunNmsClient
  ��    �ܣ� �������ܿͻ��˳��� 
  ��    ���� char* szPath [in] ���ܿͻ���·����
  �� �� ֵ�� BOOL  
=============================================================================*/
	BOOL GuiRunNmsClient(char* szPath);

/*=============================================================================
  �� �� ���� SetGuiMainWindow
  ��    �ܣ� ����Ӧ�ó����Ƿ���ڣ�����������GuiUnit�������ھ�� 
			 Ӧ���ں���GuiRunNmsClient���ú��ٵ��ô˺���
  ��    ���� int nTimeOut [in] ����Ӧ�ó���ʱʱ��(ʱ�䵥λ������)
  ˵��	  �� ��ΪӦ�ó���������Ҫһ��ʱ�䣬���ڴ�ʱ���ڻ�û�в�׽��Ӧ�ó��򽫷���false
  �� �� ֵ�� BOOL   
=============================================================================*/
	BOOL SetGuiMainWindow(int nTimeOut = 0);

/*=============================================================================
  �� �� ���� ConnectNms
  ��    �ܣ� �������ܷ�����  
  ��    ���� LPCTSTR szIp	[in] IP��ַ
             LPCTSTR szPort	[in] �˿ں�
             LPCTSTR szUser	[in] �û���
             LPCTSTR szPwd	[in] ����
  �� �� ֵ�� BOOL   
=============================================================================*/
	BOOL ConnectNms(LPCTSTR szIp, DWORD dwPort, LPCTSTR szUser, LPCTSTR szPwd);

/*=============================================================================
  �� �� ���� GuiInitUIHandle
  ��    �ܣ� ��¼���ʼ������Ԫ�ؾ��
  ��    ���� 
  �� �� ֵ�� BOOL  
=============================================================================*/
	BOOL GuiInitUIHandle();

/*=============================================================================
  �� �� ���� SetOprDelay
  ��    �ܣ� �����Ƿ������ʱ��Ĭ��Ϊ��ʱ�� 
  ��    ���� BOOL bDelay [in] true-��ʱ, false-����ʱ
  �� �� ֵ�� void  
=============================================================================*/
inline void SetOprDelay(BOOL bDelay = TRUE)
{
	m_bOprDelay = bDelay;
}

/*=============================================================================
  �� �� ���� DeviceAdd
  ��    �ܣ� �����豸
  ��    ���� TEqpAdd &tEqpadd	[in]Ҫ���ӵ��豸��Ϣ             
             LPCTSTR szDir      [in]���̷��䵽���豸������Ϊ�����ʾ������
  �� �� ֵ�� BOOL  
=============================================================================*/
    BOOL DeviceAdd(TEqpAdd &tEqpadd, LPCTSTR szDir = NULL, BOOL bOK = TRUE);
    BOOL DeviceAdd(const vector<TEqpAdd> &vecEqpadd, LPCTSTR szDir = NULL);

    BOOL DeviceAdd_EqpListPopMenu(TEqpAdd &tEqpadd, LPCTSTR szDir = NULL, BOOL bOK = TRUE);
    BOOL DeviceAdd_EqpListPopMenu(const vector<TEqpAdd> &vecEqpadd, LPCTSTR szDir = NULL);

    BOOL DeviceAdd_DirTreePopMenu(TEqpAdd &tEqpadd, LPCTSTR szDir = NULL, BOOL bOK = TRUE);
    BOOL DeviceAdd_DirTreePopMenu(const vector<TEqpAdd> &vecEqpadd, LPCTSTR szDir = NULL);
/*=============================================================================
  �� �� ���� DirCreate
  ��    �ܣ� �����豸�� 
  ��    ���� LPCTSTR szName	[in]�豸������
             LPCTSTR szSuperName [in]���豸������
  �� �� ֵ�� BOOL  
=============================================================================*/
    BOOL DirCreate(LPCTSTR szName, LPCTSTR szSuperName = NULL, BOOL bOK = TRUE);

    BOOL DirCreate_DirTreePopMenu(LPCTSTR szName, LPCTSTR szSuperName = NULL, BOOL bOK = TRUE);

/*=============================================================================
  �� �� ���� EqpMock
  ��    �ܣ� mcu�豸���ܹ���ͼ��ʾ�͵������ (��ScrollView����������δʵ�֣��˹���Ŀǰ����ʵ��)
  ��    ���� LPCTSTR szName [in] Ҫ������mcu����
			 BYTE byLayer [in] �������ڲ�� (���¶���: 1...4)
			 BYTE bySlot [in] �������ڲۺ� (�������: 1...17)
			 BYTE byOprId [in] �������ID
  �� �� ֵ�� BOOL 
=============================================================================*/
	BOOL EqpMcuMock(LPCTSTR szName, BYTE byLayer, BYTE bySlot, BYTE byOprId);

/*=============================================================================
  �� �� ���� SnmpTest
  ��    �ܣ� SNMP���� 
  ��    ���� LPCTSTR szName [in] �豸����
  �� �� ֵ�� BOOL   
=============================================================================*/
	BOOL SnmpTest(LPCTSTR szName);

/*=============================================================================
  �� �� ���� SyncTime
  ��    �ܣ� ʱ��ͬ�� 
  ��    ���� LPCTSTR szName [in] �豸����
  �� �� ֵ�� BOOL   
=============================================================================*/
	BOOL SyncTime(LPCTSTR szName);
    BOOL SyncTime(const vector<CString>& vecName);

/*=============================================================================
  �� �� ���� SyncAlarm
  ��    �ܣ� �澯ͬ�� 
  ��    ���� LPCTSTR szName [in] �豸����
  �� �� ֵ�� BOOL   
=============================================================================*/
	BOOL SyncAlarm(LPCTSTR szName);
	BOOL SyncAlarm(const vector<CString>& vecName);

/*=============================================================================
  �� �� ���� EqpCurAlarm
  ��    �ܣ� ѡ���豸�ĵ�ǰ�澯��ѯ
  ��    ���� LPCTSTR szName [in] �豸����
  �� �� ֵ�� BOOL   
=============================================================================*/
	BOOL EqpCurAlarm(LPCTSTR szName);

/*=============================================================================
  �� �� ���� EqpHisAlarm
  ��    �ܣ� ѡ���豸����ʷ�澯��ѯ
  ��    ���� LPCTSTR szName [in] �豸����
  �� �� ֵ�� BOOL   
=============================================================================*/
	BOOL EqpHisAlarm(LPCTSTR szName);

/*=============================================================================
  �� �� ���� RemoteReset
  ��    �ܣ� Զ�̸�λ 
  ��    ���� LPCTSTR szName [in] �豸����
  �� �� ֵ�� BOOL   
=============================================================================*/
	BOOL RemoteReset(LPCTSTR szName);
	BOOL RemoteReset(const vector<CString>& vecName);

/*=============================================================================
  �� �� ���� FtpDownload
  ��    �ܣ� �ļ����� 
  ��    ���� TFileUpDown &tFileDown [in] ���ز���
  �� �� ֵ�� BOOL   
=============================================================================*/
	BOOL FtpDownload(TFileUpDown &tFileDown, BOOL bOK = TRUE);

/*=============================================================================
  �� �� ���� FtpUpload
  ��    �ܣ� �ļ��ϴ� 
  ��    ���� TFileUpDown &tFileUp [in]�ϴ�����
  �� �� ֵ�� BOOL   
=============================================================================*/
	BOOL FtpUpload(vector<CString> vecEqpName, vector<CString> vecFileName,
        CString strFilePath = _T(""), BOOL bOK = TRUE);

/*=============================================================================
  �� �� ���� PingTest
  ��    �ܣ� ��·���� 
  ��    ���� TPingTest &tPingTest		[in] ping���Բ���			
  �� �� ֵ�� BOOL   
=============================================================================*/
	BOOL PingTest(TPingTest &tPingTest, BOOL bOK = TRUE);

/*=============================================================================
  �� �� ���� EqpDelete
  ��    �ܣ� �豸ɾ�� 
  ��    ���� LPCTSTR szName [in] �豸����
  �� �� ֵ�� BOOL   
=============================================================================*/
	BOOL EqpDelete(LPCTSTR szName, BOOL bOK = TRUE);
    BOOL EqpDelete(const vector<CString>& vecName, BOOL bOK = TRUE); //����  [zhuyr][2/22/2005]

/*=============================================================================
  �� �� ���� EqpMcuProperty
  ��    �ܣ� MCU�豸���� 
  ��    ���� TMcuCfgInfo &tMcuCfg [in] mcu�豸������Ϣ
  �� �� ֵ�� BOOL   
=============================================================================*/
	BOOL EqpMcuProperty(TMcuCfgInfo &tMcuCfg, BOOL bOK = TRUE);

/*=============================================================================
  �� �� ���� GuiActive
  ��    �ܣ� �����ܿͻ�����Ϊ��ǰ���� 
  �� �� ֵ�� BOOL  
=============================================================================*/
	BOOL GuiActive();

/*=============================================================================
  �� �� ���� GuiToEqp
  ��    �ܣ� �л����豸�������
  �� �� ֵ�� BOOL  
=============================================================================*/
	BOOL GuiToEqp();

/*=============================================================================
  �� �� ���� GuiToUser
  ��    �ܣ� �л����û��������
  �� �� ֵ�� BOOL   
=============================================================================*/
	BOOL GuiToUser();

/*=============================================================================
  �� �� ���� GuiToHisAlarm
  ��    �ܣ� �л�����ʷ�澯�������   
  �� �� ֵ�� BOOL   
=============================================================================*/
	BOOL GuiToHisAlarm();

/*=============================================================================
  �� �� ���� GuiToLog
  ��    �ܣ� �л�����־������� 
  �� �� ֵ�� BOOL  
=============================================================================*/
	BOOL GuiToLog();

/*=============================================================================
  �� �� ���� GuiToCurAlarm
  ��    �ܣ� ��ǰ�澯��ѯ  
  �� �� ֵ�� BOOL  
=============================================================================*/
	BOOL GuiToCurAlarm();

/*=============================================================================
  �� �� ���� GuiToAlarmKB
  ��    �ܣ� �澯֪ʶ���ѯ   
  �� �� ֵ�� BOOL  
=============================================================================*/
	BOOL GuiToAlarmKB();

    BOOL DeleteAlarmKB(DWORD dwAlarmCode, BOOL bOK = TRUE);
    BOOL AddAlarmKB(TAlarmKB& tAddAlarmKB, BOOL bOK = TRUE);
    BOOL ModifyAlarmKB(TAlarmKB& tModifyAlarmKB, BOOL bOK = TRUE);

/*=============================================================================
  �� �� ���� NmcLogOff
  ��    �ܣ� ע��  
  �� �� ֵ�� BOOL  
=============================================================================*/
	BOOL NmcLogOff(BOOL bOK = TRUE);

/*=============================================================================
  �� �� ���� NmcExit
  ��    �ܣ� �˳�
  �� �� ֵ�� BOOL  
=============================================================================*/
	BOOL NmcExit(BOOL bOK = TRUE);

/*=============================================================================
  �� �� ���� GuiToMock
  ��    �ܣ� �л���ѡ��mcu�豸�Ļ��ܹ�����ͼ 
  ��    ���� LPCTSTR szName [in] Ҫ������mcu����
  �� �� ֵ�� BOOL  
=============================================================================*/
	BOOL GuiToMock(LPCTSTR szName);

/*=============================================================================
  �� �� ���� HisAlarmQuery
  ��    �ܣ� ��ʷ�澯��ѯ  
  ��    ���� THisAlarmCondition &tCondition [in] ��ѯ����
  �� �� ֵ�� BOOL  
=============================================================================*/
	BOOL HisAlarmQuery(THisAlarmCondition &tCondition);

/*=============================================================================
  �� �� ���� DeleteAllHisAlarm
  ��    �ܣ� ɾ����ʷ�澯  
  ��    ���� LPCTSTR lpszSerial [in] �澯������
  �� �� ֵ�� BOOL  
=============================================================================*/
    BOOL DeleteAllHisAlarm(BOOL bOK = TRUE);
    BOOL DeleteHisAlarm(LPCTSTR lpszSerial, BOOL bOK = TRUE);

/*=============================================================================
  �� �� ���� HisAlarmAddToKB
  ��    �ܣ� �澯��ӵ�֪ʶ��  
  ��    ���� LPCTSTR lpszSerial [in] �澯������
             LPCTSTR lpszAlarmNo [in] �澯��ţ�����ʷ�澯��ͬ��
  �� �� ֵ�� BOOL  
=============================================================================*/
    BOOL HisAlarmAddToKB(LPCTSTR lpszSerial);
    BOOL CurAlarmAddToKB(LPCTSTR lpszAlarmNo);

/*=============================================================================
  �� �� ���� LogQuery
  ��    �ܣ� ������־��ѯ  
  ��    ���� TLogCondition &tCondition	[in] ��ѯ����
  �� �� ֵ�� BOOL  
=============================================================================*/
	BOOL LogQuery(TLogCondition &tCondition);

/*=============================================================================
  �� �� ���� DeleteAllLog
  ��    �ܣ� ɾ��������־  
  ��    ���� s8* lpszSerial	[in] ��־������
  �� �� ֵ�� BOOL  
=============================================================================*/
	BOOL DeleteAllLog(BOOL bOK = TRUE);
    BOOL DeleteLog(s8* lpszSerial, BOOL bOK = TRUE);

/*=============================================================================
  �� �� ���� UserAdd
  ��    �ܣ� ����û�  
  ��    ���� TUserBaseInfo &tUserInfo	[in]	Ҫ��ӵ��û���Ϣ
  �� �� ֵ�� BOOL  
=============================================================================*/
	BOOL UserAdd(TUserBaseInfo &tUserInfo);

/*=============================================================================
  �� �� ���� UserModify
  ��    �ܣ� �޸��û���Ϣ 
  ��    ���� TUserBaseInfo &tUserInfo [in] Ҫ�޸ĵ��û���Ϣ
  �� �� ֵ�� BOOL  
=============================================================================*/
	BOOL UserModify(TUserBaseInfo &tUserInfo);

/*=============================================================================
  �� �� ���� UserDel
  ��    �ܣ� ɾ��ָ���û�  
  ��    ���� LPCTSTR szUserName [in] Ҫɾ�����û���
  �� �� ֵ�� BOOL   
=============================================================================*/
	BOOL UserDel(LPCTSTR szUserName, BOOL bOK = TRUE);

	BOOL UserDel_UserTreePopMenu(LPCTSTR szUserName, BOOL bOK = TRUE);

/*=============================================================================
  �� �� ���� UserAddPriv
  ��    �ܣ� Ϊָ���û�����Ȩ����   
  ��    ���� TUserWithGroup &tUserAddPriv				[in] Ҫ����Ȩ�޵��û���Ϣ
  �� �� ֵ�� BOOL   
=============================================================================*/
	BOOL UserAddPriv(TUserWithGroup &tUserAddPriv, BOOL bOK = TRUE);

    BOOL UserAddPriv_UserTreePopMenu(TUserWithGroup &tUserAddPriv, BOOL bOK = TRUE);

/*=============================================================================
  �� �� ���� UserDelPriv
  ��    �ܣ� Ϊָ���û�ȡ��������Ȩ����  
  ��    ���� TUserWithGroup &tUserDelPriv				[in]Ҫȡ���������û���Ϣ
  �� �� ֵ�� BOOL   
=============================================================================*/
	BOOL UserDelPriv(TUserWithGroup &tUserDelPriv);

	BOOL UserDelPriv_UserTreePopMenu(TUserWithGroup &tUserDelPriv, BOOL bOK = TRUE);

/*=============================================================================
  �� �� ���� GroupAdd
  ��    �ܣ� ����û��� 
  ��    ���� TGroupBaseInfo &tGroupInfo [in] Ҫ��ӵ��û�����Ϣ
  �� �� ֵ�� BOOL  
=============================================================================*/
	BOOL GroupAdd(TGroupBaseInfo &tGroupInfo);

/*=============================================================================
  �� �� ���� GroupModify
  ��    �ܣ� �޸�ָ���û���  
  ��    ���� TGroupBaseInfo &tGroupInfo [in] Ҫ�޸ĵ��û���
  �� �� ֵ�� BOOL  
=============================================================================*/
	BOOL GroupModify(TGroupBaseInfo &tGroupInfo);

/*=============================================================================
  �� �� ���� GroupDel
  ��    �ܣ� ɾ��ָ���û��� 
  ��    ���� LPCTSTR szGroupName [in] Ҫɾ�����û�����
  �� �� ֵ�� BOOL   
=============================================================================*/
	BOOL GroupDel(LPCTSTR szGroupName, BOOL bOK = TRUE);

/*=============================================================================
  �� �� ���� GroupAddMember
  ��    �ܣ� Ϊָ��Ȩ��������û���Ա 
  ��    ���� TUserWithGroup &tGroupAddMem		[in] Ҫ����û���Ա��Ȩ����Ϣ
  �� �� ֵ�� BOOL   
=============================================================================*/
	BOOL GroupAddMember(TUserWithGroup &tGroupAddMem, BOOL bOK = TRUE);

	BOOL GroupAddMember_UserTreePopMenu(TUserWithGroup &tGroupAddMem, BOOL bOK = TRUE);

/*=============================================================================
  �� �� ���� GroupDelMember
  ��    �ܣ� ɾ��ָ��Ȩ�����е��û���Ա  
  ��    ���� TUserWithGroup &tGroupDelMem		[in] Ҫɾ���û���Ա��Ȩ����Ϣ
  �� �� ֵ�� BOOL  
=============================================================================*/
	BOOL GroupDelMember(TUserWithGroup &tGroupDelMem);

/*=============================================================================
  �� �� ���� ModifyCurUserPwd
  ��    �ܣ� �޸ĵ�ǰ�û����� 
  ��    ���� TModifyUserPwd &tModifyPwd	[in] ������Ϣ
  �� �� ֵ�� BOOL   
=============================================================================*/
	BOOL ModifyCurUserPwd(TModifyUserPwd &tModifyPwd, BOOL bOK = TRUE);

/*=============================================================================
  �� �� ���� AlarmFilter
  ��    �ܣ� �澯���� 
  ��    ���� TEqpAlarmFilter &tAlarmFilter  [in] Ҫ���˵ĸ澯��Ϣ
  �� �� ֵ�� BOOL   
=============================================================================*/
	BOOL AlarmFilter(TEqpAlarmFilter &tAlarmFilter, BOOL bOK = TRUE);

/*=============================================================================
  �� �� ���� GroupPrivSet
  ��    �ܣ� �û���Ȩ���豸  
  ��    ���� TGroupPriv &tGroupPriv [in] Ҫ���õ�Ȩ����Ϣ			 
  �� �� ֵ�� BOOL  
=============================================================================*/
	BOOL GroupPrivSet(TGroupPriv &tGroupPriv, BOOL bOK = TRUE);

	BOOL GroupPrivSet_UserTreePopMenu(TGroupPriv &tGroupPriv, BOOL bOK = TRUE);

/*=============================================================================
  �� �� ���� DirAddMember,DirDelMember
  ��    �ܣ� �豸��(ȡ��)�����豸  
  ��    ���� LPCTSTR szDirName [in] Ҫ���õ��豸��
             LPCTSTR szDeviceName [in] Ҫ���õ��豸 NULLΪȫ��
  �� �� ֵ�� BOOL  
=============================================================================*/
	BOOL DirAddMember(LPCTSTR szDirName, LPCTSTR szDeviceName, BOOL bOK = TRUE);
    BOOL DirAddMember(LPCTSTR vecDirName, const vector<CString>& szDeviceName);
	BOOL DirDelMember(LPCTSTR szDirName, LPCTSTR szDeviceName, BOOL bOK = TRUE);
    BOOL DirDelMember(LPCTSTR szDirName, const vector<CString>& szDeviceName);

/*=============================================================================
  �� �� ���� DirDelete
  ��    �ܣ� ɾ���豸��
  ��    ���� LPCTSTR szDirName [in] Ҫ���õ��豸��
  �� �� ֵ�� BOOL  
=============================================================================*/
    BOOL DirDelete(LPCTSTR szDirName, BOOL bOK = TRUE);

/*=============================================================================
  �� �� ���� DirResresh
  ��    �ܣ� ˢ���豸����豸  
  ��    ���� LPCTSTR szDirName [in] Ҫ���õ��豸��
  �� �� ֵ�� BOOL  
=============================================================================*/
    BOOL DirResresh(LPCTSTR szDirName);
    
    BOOL DirResresh_EqpListPopMenu(LPCTSTR szDirName);

/*=============================================================================
  �� �� ���� DirArrange
  ��    �ܣ� ˢ���豸����豸  
  ��    ���� LPCTSTR szDirName [in] Ҫ���е��豸��
  �� �� ֵ�� BOOL  
=============================================================================*/
    BOOL DirArrange(LPCTSTR szDirName);
    
    BOOL DirArrange_EqpListPopMenu(LPCTSTR szDirName);


/*=============================================================================
  �� �� ���� DirPros
  ��    �ܣ� �豸�������
  ��    ���� LPCTSTR szDirName [in] Ҫ���õ��豸��
  �� �� ֵ�� BOOL  
=============================================================================*/
    BOOL DirPros(LPCTSTR szDirName, BOOL bOK = TRUE);
    BOOL DirPros_EqpListPopMenu(LPCTSTR szDirName, BOOL bOK = TRUE);
    
    BOOL ClearAllDir();
    BOOL ClearDevice();
protected:
/*=============================================================================
  �� �� ���� MoveBtnClick
  ��    �ܣ� ģ������ƶ�����ť�ϵ��� 
  ��    ���� HWND hWnd [in] ��ť���
  �� �� ֵ�� void  
=============================================================================*/
	BOOL MoveBtnClick(HWND hWnd);

/*=============================================================================
  �� �� ���� MoveTextInput
  ��    �ܣ� ģ������ƶ���Edit�ؼ��������ı� 
  ��    ���� CString strData	[in] ������ı�
             HWND hWnd			[in] Edit�ؼ����
  �� �� ֵ�� void  
=============================================================================*/
	void MoveTextInput(CString strData, HWND hWnd);	

/*=============================================================================
  �� �� ���� CbEditChange
  ��    �ܣ� edit�ؼ����ݷ����仯ʱ������Ϣ֪ͨ(��ΪGuiUnit����û�з��ʹ���Ϣ)
  ��    ���� UINT uCtrlId	[in]�ؼ�id
             UINT uMsg		[in]Ҫ���͵���Ϣid
             HWND hCtrl		[in]�ؼ����
             HWND hParent	[in]�ؼ����ڸ����ھ��
  �� �� ֵ�� BOOL  
=============================================================================*/
	BOOL EditChange(UINT uCtrlId, UINT uMsg, HWND hCtrl, HWND hParent);

/*=============================================================================
  �� �� ���� ErrorDeal
  ��    �ܣ� ������ʾ����������ʾ����ص�
  ��    ���� HWND hParent
  �� �� ֵ�� BOOL [in]	�����ھ��
=============================================================================*/
	BOOL ErrorDeal(const HWND hParent);

/*=============================================================================
  �� �� ���� EqpRClickMenu
  ��    �ܣ� �豸�б���ͼ�Ҽ��˵�����  
  ��    ����LPCTSTR szName	[in] �����豸����
			UINT uOprID		[in] ������id
  �� �� ֵ�� BOOL 
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2004/10/21    3.5			������                  ����
=============================================================================*/
	BOOL EqpRClickMenu(LPCTSTR szName, UINT uOprID, UINT nTime = 1, BOOL bOK = TRUE);

/*=============================================================================
  �� �� ���� TreeDirRClickMenu
  ��    �ܣ� �豸����ͼ�Ҽ��˵�����  
  ��    ����LPCTSTR szName	[in] �����豸����
			UINT uOprID		[in] ������id
  �� �� ֵ�� BOOL 
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2004/12/02    3.5			������                  ����
=============================================================================*/
    BOOL TreeDirRClickMenu(LPCTSTR szName, UINT uOprID);

/*=============================================================================
  �� �� ���� TreeDirSelectItem
  ��    �ܣ� �豸Ŀ¼����ͼ��ѡ��ĳ��item  
  ��    ���� LPCTSTR szName [in] Ҫѡ��item���ı�, szNameΪ�ձ�ʾ��
  �� �� ֵ�� BOOL  
=============================================================================*/
	BOOL TreeDirSelectItem(LPCTSTR szName = NULL);

/*=============================================================================
  �� �� ���� UpdateUserInfo
  ��    �ܣ� ��ӻ��޸��û�ʱ�����û���Ϣ   
  ��    ���� TUserBaseInfo &tUserInfo [in] Ҫ���µ��û���Ϣ
  �� �� ֵ�� BOOL   
=============================================================================*/
	BOOL UpdateUserInfo(TUserBaseInfo &tUserInfo);

/*=============================================================================
  �� �� ���� TreeUserRClickMenu
  ��    �ܣ� �û�����ͼ��ĳ��item�ĵ����˵�����
  ��    ���� LPCTSTR szName [in] Ҫѡ��item���ı�, szName Ϊ�ձ�ʾ�û�or���
			 BOOL bUser [in] �û�or�������Ĭ��Ϊ�û�
  �� �� ֵ�� BOOL  
=============================================================================*/
	BOOL TreeUserRClickMenu(LPCTSTR szName, UINT uOprID, BOOL bUser = TRUE);

/*=============================================================================
  �� �� ���� TreeUserSelectItem
  ��    �ܣ� ����ͼ��ѡ��ĳ��item  
  ��    ���� LPCTSTR szName [in] Ҫѡ��item���ı�, szName Ϊ�ձ�ʾ�û�or���
			 BOOL bUser [in] �û�or�������Ĭ��Ϊ�û�
  �� �� ֵ�� BOOL  
=============================================================================*/
	BOOL TreeUserSelectItem(LPCTSTR szName, BOOL bUser = TRUE);

/*=============================================================================
  �� �� ���� UpdateMcuProsPeri
  ��    �ܣ� mcu���������и�������������Ϣ 
  ��    ���� BYTE byPeriType	[in] ��������
			 vector<CString> vtPeriInfo [in] Ҫ���µ�������Ϣ
  �� �� ֵ�� BOOL  
=============================================================================*/
	BOOL UpdateMcuProsPeri(BYTE byPeriType, vector<CString> &vtPeriInfo, BOOL bOK = TRUE);

/*=============================================================================
  �� �� ���� MixerCfg2Str
  ��    �ܣ� ������������ת��Ϊ�ַ������� 
  ��    ���� TMixerCfg &tMixerCfg [in] ����������
			 vector<CString> [in/out] �ַ���������ʽ�Ļ���������
  �� �� ֵ��  
=============================================================================*/
	void MixerCfg2Str(TMixerCfg &tMixerCfg, vector<CString> &vtMixer);

/*=============================================================================
  �� �� ���� RecCfg2Str
  ��    �ܣ� ��¼�������ת��Ϊ�ַ������� 
  ��    ���� TRecCfg &tRecCfg [in] ¼�������
			 vector<CString>  [in/out] �ַ���������ʽ��¼������� 
  �� �� ֵ��  
=============================================================================*/
	void RecCfg2Str(TRecCfg &tRecCfg, vector<CString> &vtRec);

/*=============================================================================
  �� �� ���� TWCfg2Str
  ��    �ܣ� ������ǽ����ת��Ϊ�ַ�������   
  ��    ���� TTVWallCfg &tTWCfg [in] ����ǽ����
			 vector<CString>   [in/out] �ַ���������ʽ�ĵ���ǽ���� 
  �� �� ֵ�� 
=============================================================================*/
	void TWCfg2Str(TTVWallCfg &tTWCfg, vector<CString> &vtTW);

/*=============================================================================
  �� �� ���� TBasVmpCfg2Str
  ��    �ܣ� ��������������ϳ�������ת��Ϊ�ַ�������  
  ��    ���� BasVmpCfg &tBasVmpCfg [in] ����������ϳ�������
			 vector<CString>  [in/out] �ַ���������ʽ�Ĳ���  
  �� �� ֵ�� 
=============================================================================*/
	void BasVmpCfg2Str(TVmpCfg &tBasVmpCfg, vector<CString> &vtBasVmp);
	void BasCfg2Str(TBasVmpCfg &tBasVmpCfg, vector<CString> &vtBasVmp);

/*=============================================================================
  �� �� ���� McuProsBasicInfo
  ��    �ܣ� mcu�豸���ԣ�������Ϣ���� 
  ��    ���� TMcuCfgInfo &cMcuCfg [in] mcu������Ϣ
  �� �� ֵ�� BOOL  
=============================================================================*/
	BOOL McuProsBasicInfo(TMcuCfgInfo &tMcuCfg);

/*=============================================================================
  �� �� ���� McuProsNet
  ��    �ܣ� mcu�豸���ԣ��������� 
  ��    ���� TMcuCfgInfo &cMcuCfg [in] mcu������Ϣ
  �� �� ֵ�� BOOL  
=============================================================================*/
	BOOL McuProsNet(TMcuCfgInfo &tMcuCfg);

/*=============================================================================
  �� �� ���� McuProsBrd
  ��    �ܣ� mcu�豸���ԣ���������  
  ��    ���� TMcuCfgInfo &cMcuCfg [in] mcu������Ϣ
  �� �� ֵ�� BOOL  
=============================================================================*/
	BOOL McuProsBrd(TMcuCfgInfo &tMcuCfg);

/*=============================================================================
  �� �� ���� McuProsPeri1
  ��    �ܣ� mcu�豸���ԣ�����1���� 
  ��    ���� TMcuCfgInfo &cMcuCfg [in] mcu������Ϣ
  �� �� ֵ�� BOOL   
=============================================================================*/
	BOOL McuProsPeri1(TMcuCfgInfo &tMcuCfg);

/*=============================================================================
  �� �� ���� McuProsPeri2
  ��    �ܣ� mcu�豸���ԣ�����2���� 
  ��    ���� TMcuCfgInfo &cMcuCfg [in] mcu������Ϣ
  �� �� ֵ�� BOOL   
=============================================================================*/
	BOOL McuProsPeri2(TMcuCfgInfo &tMcuCfg);

/*=============================================================================
  �� �� ���� McuProsPrs
  ��    �ܣ� mcu�豸���ԣ����ش�����  
  ��    ���� TMcuCfgInfo &cMcuCfg [in] mcu������Ϣ
  �� �� ֵ�� BOOL  
=============================================================================*/
	BOOL McuProsPrs(TMcuCfgInfo &tMcuCfg);

/*=============================================================================
  �� �� ���� McuProsNetSync
  ��    �ܣ� mcu�豸���ԣ���ͬ������ 
  ��    ���� TMcuCfgInfo &cMcuCfg [in] mcu������Ϣ
  �� �� ֵ�� BOOL  
=============================================================================*/
	BOOL McuProsNetSync(TMcuCfgInfo &tMcuCfg);

/*=============================================================================
  �� �� ���� TBMenuClick
  ��    �ܣ� ʵ��������������˵�����  
  ��    ���� BYTE byMenu	[in] �˵�id
             BYTE byOprId	[in] Ҫʵ�ֵĲ���id
  �� �� ֵ�� BOOL  
=============================================================================*/
	BOOL TBMenuClick(BYTE byMenu, BYTE byOprId);

/*=============================================================================
  �� �� ���� ListCtrlMenuClick
  ��    �ܣ� ListCtrl�ؼ����Ҽ��˵�����  
  ��    ���� CString csName	[in] �������Ƶ���
			 BYTE byOprId   [in] Ҫʵ�ֵĲ���id
             HWND hListCtrl	[in] �ؼ����
  �� �� ֵ�� BOOL  
=============================================================================*/
	BOOL ListCtrlMenuClick(CString csName, BYTE byOprId, HWND hListCtrl);

/*=============================================================================
  �� �� ���� ListCtrlMenuClick
  ��    �ܣ� ListCtrl�ؼ����Ҽ��˵����� 
  ��    ���� int nIndex		[in] ������������
			 BYTE byOprId   [in] Ҫʵ�ֵĲ���id
             HWND hListCtrl [in] �ؼ����
  �� �� ֵ�� BOOL  
=============================================================================*/
	BOOL ListCtrlMenuClick(int nIndex, BYTE byOprId, HWND hListCtrl);

/*=============================================================================
  �� �� ���� ListBoxSelect
  ��    �ܣ� ѡ��ĳһ��item 
  ��    ���� CString csText	[in] Ҫѡ�е�item�ı�
             HWND hListBox	[in] listbox���
  �� �� ֵ�� BOOL  
=============================================================================*/
	BOOL ListBoxSelect(CString csText, HWND hListBox);
    
    BOOL DeleteTreeItem(HTREEITEM hItem, HWND hWnd, BOOL bDelThis = TRUE);

    BOOL SetAlarmKB(TAlarmKB& tModifyAlarmKB, BOOL bModify = TRUE, BOOL bOK = TRUE);
    BOOL SetAlarmKBList(TAlarmKB& tModifyAlarmKB);

//������һЩ�����ľ���ִ�н׶Σ��б��ڴ����׶Σ�������˵���ɲο���Ӧ�Ĳ���
    BOOL DoDeviceAdd(TEqpAdd &tEqpadd, BOOL bOK = TRUE);
    BOOL DoDeviceAdd(const vector<TEqpAdd> &vecEqpadd);
	BOOL DoDirCreate(LPCTSTR szName, BOOL bOK = TRUE);
	BOOL DoUserDel(LPCTSTR szUserName, BOOL bOK = TRUE);
	BOOL DoUserAddPriv(TUserWithGroup &tUserAddPriv, BOOL bOK = TRUE);
	BOOL DoUserDelPriv(TUserWithGroup &tUserAddPriv, BOOL bOK = TRUE);
	BOOL DoGroupAddMember(TUserWithGroup &tGroupAddMem, BOOL bOK = TRUE);
	BOOL DoGroupPrivSet(TGroupPriv &tGroupPriv, BOOL bOK = TRUE);
    BOOL DoDirPros(LPCTSTR szDirName, BOOL bOK = TRUE);

protected:
	//����������ӿ�
	CGuiUnit			m_cGuiUnit;
	//��ǰ���ڽ���λ��
	int					m_nCurGuiPos;
	//�Ƿ���ʱ�Ŀ���,Ĭ��Ϊ��ʱ
	BOOL				m_bOprDelay;

    HWND                m_hMain;    //������  

	//����Ԫ�ؾ��---���¾����GuiInitUIHandle()�г�ʼ��
	HWND m_hTbMenu;			//�˵���
	
	//�豸�������
	HWND m_hTreeEqp;		//�豸������-left
	HWND m_hListEqp;		//�豸�б�	-right

	//��ʷ�澯����
	HWND m_hDlgHisAlarm;	//��ʷ�澯�Ի���
	HWND m_hCbAlmType;		//�澯���
	HWND m_hEtEqpId;		//�豸���
	HWND m_hCbtnAlmRand[3];	//�澯����
	HWND m_hRdAlmCrTime[4];	//�澯����ʱ��ѡ��
	HWND m_hEtCrLastMonth;	//ǰ N ����
	HWND m_hEtCrLastDay;	//ǰ N ��
	HWND m_hDpCrStartDate;	//����
	HWND m_hDpCrStartTime;
	HWND m_hDpCrEndDate;
	HWND m_hDpCrEndTime;
	HWND m_hRdAlmRsTime[4];	//�澯�ָ�ʱ��ѡ��
	HWND m_hEtRsLastMonth;	//ǰ N ����
	HWND m_hEtRsLastDay;	//ǰ N ��
	HWND m_hDpRsStartDate;	//����
	HWND m_hDpRsStartTime;
	HWND m_hDpRsEndDate;
	HWND m_hDpRsEndTime;
	HWND m_hBtnAlmStartSch;	//�澯����
	HWND m_hBtnAlmStopSch;	//ֹͣ����
	HWND m_hBtnAlmDel;		//ɾ��

	//�û�����
	HWND m_hDlgUser;		//�û�����Ի���
	HWND m_hTreeUser;		//TreeView �û�����
	HWND m_hEtUserId;		//�û����
	HWND m_hEtUserLog;		//��¼����
	HWND m_hEtUserPass[2];	//��¼����
	HWND m_hEtUserName;		//����
	HWND m_hRtUserSex[2];	//�Ա�
	HWND m_hEtUserPho;		//�绰
	HWND m_hEtUserMoPh;		//�ֻ�
	HWND m_hEtUserBeep;		//����
	HWND m_hEtUserEMail;	//E_mail
	HWND m_hEtUserDepart;	//��λ
	HWND m_hEtUserAddr;		//סַ
	HWND m_hEtUserDetail;	//��ע
	HWND m_hBtnUserSave;	//����
	HWND m_hBtnUserModify;	//�޸�
	HWND m_hBtnUserDel;		//ɾ��
	HWND m_hListUserInfo;	//Ȩ����Ϣ�б�
	HWND m_hBtnUserAddGp;	//�����
	HWND m_hBtnUserDelGp;	//ɾ����
	HWND m_hBtnUserCalcu;	//ͳ��Ȩ��
	
	//�����
	HWND m_hDlgGroup;		//�����Ի���
	HWND m_hEtGrpName;		//����
	HWND m_hEtGrpDetail;	//����
	HWND m_hBtnGrpCreat;	//����
	HWND m_hBtnGrpModify;	//�޸�
	HWND m_hBtnGrpDel;		//ɾ��
	HWND m_hListMembList;	//��Ա�б�
	HWND m_hBtnMembAdd;		//���
	HWND m_hBtnMembDel;		//ɾ��
	HWND m_hListGrpDetail;	//Ȩ����Ϣ
	HWND m_hBtnPwerSet;		//����
	
	//��־����
	HWND m_hDlgLog;			//��־����Ի���
	HWND m_hEtLogUserName;	//�û���
	HWND m_hBtnSelAll;		//ȫѡ
	HWND m_hBtnUnSelAll;	//ȫ��ѡ
	HWND m_hListBoxOprType; //���������б��
	HWND m_hRdLogRsTime[4];	//�澯�ָ�ʱ��ѡ��
	HWND m_hEtLogLastMonth;	//ǰ N ����
	HWND m_hEtLogLastDay;	//ǰ N ��
	HWND m_hDpLogStartDate;	//����
	HWND m_hDpLogStartTime;
	HWND m_hDpLogEndDate;
	HWND m_hDpLogEndTime;
	HWND m_hCbOprObj;		//������������
	HWND m_hEtOprName;		//������������
	HWND m_hCbtnOprId;		//����������
	HWND m_hEtOprId;		//����������
	HWND m_hCbtnOprRet[2];	//����������
	HWND m_hBtnLogStartSch;	//��ʼ����
	HWND m_hBtnLogStopSch;	//ֹͣ����
	HWND m_hBtnLogDel;		//ɾ����־
};
#endif // #define __NMSCLIENTINTTESTUIEX_H
