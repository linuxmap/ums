/*****************************************************************************
ģ����      : Pcmt������Կ�����ӿ�
�ļ���      : PcmtGuiTestLib.h
����ļ�    : 
�ļ�ʵ�ֹ���: ��Ԫ����
����        : �ź���
�汾        : V4.0  Copyright(C) 1997-2005 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2005/07/25  4.0         �ź���        ����
2005/08/18  4.0         �ź���        �޸�
2005/10/11  4.0         �ź���        �޸�
******************************************************************************/

#ifndef PCMTGUITESTLIB_H
#define PCMTGUITESTLIB_H

#include "cppunit\GuiUnit.h"
#include "kdvType.h"		// ��������
#include "kdvDef.h"			// ������
#include "osp.h"			// OSPҵ��
#include "tpstruct.h"		// mt���ͽṹ
#include "mtsysapi.h"
#include "dcmtdefine.h"

#include "pcmtguitestlibdefine.h" //���������ļ�

#include <vector>
using std::vector;

//	����ϳ��ն˲���
typedef struct tagVmpMt
{
    tagVmpMt()
    {
        ZeroMemory( aszMtAlias, sizeof ( aszMtAlias ) );
        byChannel       = 0;
        byMemberType    = emVMPMmbMCSspec;
    }
	s8	aszMtAlias[MT_MAX_H323ALIAS_LEN];	//	�ն˱���
	u8	byChannel;					    //	������һ��ͨ��
    u8	byMemberType;				    //	���淽ʽ
} TVmpMt;

typedef struct tagMonitorMt
{
	CString strMtName;	                //	�ն˱���
	u8	byChannel;					    //	������һ��ͨ��
} TMonitorMt;

class CPcmtGuiTestLib
{
public:
    CPcmtGuiTestLib();
    virtual ~CPcmtGuiTestLib();
private:
	/*=======================================================================
	�� �� ��: GuiActiveWindow
	��    �ܣ����������ն˴���
	��    ����
	�� �� ֵ���ɹ�����TRUE��ʧ�ܷ���FALSE
	˵    ����
	=======================================================================*/
	BOOL32 GuiActiveWindow();
	
private:
    //*****�ڲ��õĲ����ӿ�************************************************************//

	/*=======================================================================
	�������� MoveToBtn
    ��    �ܣ� �ƶ��������������ĳ����ť
    ��    ���� HWND hWnd ��ť���
    �� �� ֵ�� BOOL32 �Ƿ�ɹ�
    ˵    ��:
	=======================================================================*/
    BOOL32 MoveToBtn(HWND hWnd);    

    /*�������� InitPCMTHandle
    ��    �ܣ� ��ʼ�����
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 InitPcmtHandle();   

    /*�������� ShowCfgDlg
    ��    �ܣ� ��ʾ����ҳ
    ��    ���� szPassword: ���ÿ���
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 ShowCfgDlg(const CString& szPassword = _T(""));

    BOOL32 ChangeView(u8 byIndex);

    BOOL32 MenuClickMt(s32 nListItem, s32 nMenuItem);

    u8 GetVmpStyle(u8 byType);

public:
    //*****�ṩ���ⲿ���õĽӿ�******//

    //*****ϵͳ��ʼ���Ĳ����ӿ�********************************************************//
   
	/*=============================================================================
	�� �� ���� SetDelay
	��    �ܣ� �����Ƿ������ʱ��Ĭ��Ϊ��ʱ��
	��    ���� BOOL bDelay					[in]	true-��ʱ, false-����ʱ
	�� �� ֵ�� void
	=============================================================================*/
	inline void SetDelay(BOOL32 bDelay = TRUE)
	{
		m_bDelay = bDelay;
	}

    /*�������� GuiInit
    ��    �ܣ� ��ʼ��PCMT
    ��    ���� CString szExePath   ����·��
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 GuiInit(CString szExePath);

    /*�������� InitOP
    ��    �ܣ� �ٴγ�ʼ��������Կ�
    ��    ���� CString szTitle 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 InitOP(const CString& szTitle);
    
    
    /*�������� close
    ��    �ܣ� �رղ��Խӿ������ֳ�
    ��    ���� 
    �� �� ֵ�� void 
    ˵    ���� �˳�ʱ��õ����Ա�رղ��Զ���*/
    void Close();

    /*�������� IsInP2PConf
    ��    �ܣ� �Ƿ��ڵ�Ե������
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 IsInP2PConf();

    /*�������� IsInP2PConf
    ��    �ܣ� �Ƿ��ڵ�Ե������
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 IsCalling();

    /*�������� IsInMConf
    ��    �ܣ� �Ƿ��ڶ�������
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 IsInMConf();

    /*�������� IsChairman
    ��    �ܣ� �Ƿ���ϯ
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 IsChairman();

    /*�������� IsSpeaker
    ��    �ܣ� �Ƿ�����
    ��    ���� u8 byIndex list�ؼ��е�����
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 IsSpeaker(u8 byIndex);


    /*�������� GetSpeaker
    ��    �ܣ� 
    ��    ���� ��
    �� �� ֵ�� 
    ˵    ���� */
    CString GetSpeaker();

    /*�������� GetChairman
    ��    �ܣ� 
    ��    ���� ��
    �� �� ֵ��  
    ˵    ���� */
    CString GetChairman();


    //**********��������Խӿ�********************************************************//

    /*�������� AboutVer
    ��    �ܣ� ���ڰ汾��Ϣ
    ��    ���� 
    �� �� ֵ�� 
    ˵    ���� */
    BOOL32 AboutVer();
	
    /*�������� AboutHelp
    ��    �ܣ� ���ڰ���
    ��    ���� 
    �� �� ֵ�� 
    ˵    ���� */
    BOOL32 AboutHelp();
		
    /*�������� Dummy
    ��    �ܣ� ����
    ��    ���� BOOL32 bDummy TRUE ���� FALSE ȡ������
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 Mute(BOOL32 bMute);

    /*�������� Silent
    ��    �ܣ� ����
    ��    ���� BOOL32 bSilent TRUE ���� FALSE ȡ������
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 Silent(BOOL32 bSilent);

    /*�������� StartMonitor
    ��    �ܣ� ��ʼ���
    ��    ���� vector< TMonitorMt >& vecMt �����Ϣ
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 StartMonitor(vector< TMonitorMt >& vecMt);

    /*�������� StopMonitor
    ��    �ܣ� ֹͣ���
    ��    ���� u8 byIndex:   ���ͨ������(0 ~ 8)
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 StopMonitor(u8 byIndex);

    /*�������� RealtimeMonitor
    ��    �ܣ� ʵʱ���
    ��    ���� u8 byIndex:   ���ͨ������(0 ~ 8)
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 RealtimeMonitor(u8 byIndex);

    /*�������� StopRealtimeMonitor
    ��    �ܣ� ֹͣʵʱ���
    ��    ���� u8 byIndex:   ���ͨ������(0 ~ 8)
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 StopRealtimeMonitor(u8 byIndex);

    /*�������� LocalFullScreen
    ��    �ܣ� ����ȫ��
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 LocalFullScreen();

    /*�������� LocalSnap
    ��    �ܣ� ץ��
    ��    ���� CString& lpszPath
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 LocalSnap(const CString& szPath = _T(""));

    //************��Ե�������*****************************************************// 
    
    /*�������� MakeCall
    ��    �ܣ� ���������ն�
    ��    ���� TMtAddr tTermAddr �ն˺��нṹ 
	           u16 wBitRate ��������
               BOOL32 bAddrbook  �Ƿ�ͨ����ַ��������
			   u32 dwSleepTime   �ȴ����гɹ���������ʱ�䣬���Ϊ0���򲻵ȴ���ֱ�ӷ���
    �� �� ֵ�� BOOL32 �ɹ�����TRUE��ʧ�ܷ���FALSE
    ˵    ���� */
	BOOL32 MakeCall(const TMtAddr& tTermAddr, u16 wBitRate, BOOL32 bAddrbook = FALSE,
		            u32 dwSleepTime = 20000);

    /*�������� CancelCalling
    ��    �ܣ� ȡ������
    ��    ���� 
    �� �� ֵ�� BOOL32 �ɹ�����TRUE��ʧ�ܷ���FALSE
    ˵    ���� */
	BOOL32 CancelCalling();
    
    /*�������� EndP2PConf
    ��    �ܣ� ������Ե����
    ��    ���� 
    �� �� ֵ�� BOOL32 �ɹ�����TRUE��ʧ�ܷ���FALSE
    ˵    ���� */
	BOOL32 EndP2PConf();

    
    //************����������ӿ�************************************************// 

    /*�������� CreateConf
    ��    �ܣ� �ն˴�������
    ��    ���� const TMtAddr& tMcuInfo		Mcu����Ϣ
			   u16 wBitRate                 ��������
			   const TConfBaseInfo& info		������Ϣ
			   const vector<TMtAddr>& vMts	�ն���Ϣ
               u32 dwSleepTime              ������ȴ�ʱ�䣬���Ϊ0�򲻵ȴ���ֱ�ӷ���
    �� �� ֵ�� BOOL32 �ɹ�����TRUE��ʧ�ܷ���FALSE
    ˵    ���� */
   BOOL32 CreateConf(const TMtAddr& tMcuInfo, u16 wBitrate,const TConfBaseInfo &info, 
	                 const vector<TMtAddr>& vMts,const CString& szGroupName = "", 
					 BOOL32 bByAddrbook = FALSE, DWORD dwSleepTime = 20000); 
    
    /*�������� JoinConf
    ��    �ܣ� �ն�����������
    ��    ���� const TMtAddr& mcu [in]MCU�ĵ�ַ
               u16 &wBitRate ��������
               CString szConfName ��������
               CString szPWD ��������
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 JoinConf(const TMtAddr& mcu, u16 wBitRate, const CString& szConfName=_T(""), 
		            const CString& szPWD = "123");

	/*�������� InputConfPass
    ��    �ܣ� �����������
    ��    ���� const CString& szPassword ����
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 InputConfPwd(const CString& szPassword);		
	
    /*�������� QuitConf
    ��    �ܣ� �˳�����
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 QuitConf();

    /*�������� EndConf
    ��    �ܣ� ��������
    ��    ���� 
    �� �� ֵ�� BOOL32 �ɹ�����TRUE��ʧ�ܷ���FALSE
    ˵    ���� */
	BOOL32 EndConf();

    /*�������� DelayConf
    ��    �ܣ� �ӳ�����
    ��    ���� u32 dwTime
    �� �� ֵ�� BOOL32 �ɹ�����TRUE��ʧ�ܷ���FALSE
    ˵    ���� */
	BOOL32 DelayConf(u32 dwTime);
	
    /*�������� InviteMt
    ��    �ܣ� �����ն�
    ��    ���� const TMtAddr& tMt
               u16 &wBitRate
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 InviteMt(const TMtAddr& tMt, u16 wBitRate);

    /*�������� RevokeMt
    ��    �ܣ� �����ն�
    ��    ���� CString &szMt
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 RevokeMt(const CString& szMt);

    /*�������� ReqSpeak
    ��    �ܣ� ���뷢��
    ��    ���� 
    �� �� ֵ�� BOOL32 �ɹ�����TRUE��ʧ�ܷ���FALSE
    ˵    ���� */
	BOOL32 ReqSpeak();

    /*�������� ReqChairman
    ��    �ܣ� ������ϯ
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 ReqChairman();

    /*�������� ReqChimein
    ��    �ܣ� ����廰
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 ReqChimein();

    /*�������� SpecifySpeaker
    ��    �ܣ� ָ�������ն�
    ��    ���� CString &szMt
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 SpecifySpeaker(const CString& szMt);

    /*�������� SpecifyChairman
    ��    �ܣ� ָ����ϯ�ն�
    ��    ���� CString &szMt
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 SpecifyChairman(const CString& szMt);

    /*�������� RevokeSpeaker
    ��    �ܣ� ȡ����ǰ�����ն˵ķ���Ȩ
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 RevokeSpeaker();

    /*�������� RevokeChairman
    ��    �ܣ� ȡ����ǰ��ϯ�ն˵���ϯȨ
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 RevokeChairman();

    /*�������� StartDiscuss
    ��    �ܣ� ��ʼ����ģʽ
    ��    ���� u8 byMax      ���۵����
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 StartDiscuss(u8 byMax);

    /*�������� StopDiscuss
    ��    �ܣ� ֹͣ����ģʽ
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 StopDiscuss();

    /*�������� StartVAC
    ��    �ܣ� ��ʼ��������
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 StartVAC();

    /*�������� StopVAC
    ��    �ܣ� ֹͣ��������
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 StopVAC();

    /*�������� StartVMP
    ��    �ܣ� ��ʼ��Ƶ����
    ��    ���� u8 byType ��������
               vector<CString> &vctMT ���븴�ϵ��ն��б�
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 StartVMP(u8 byType, vector<CString> &vctMt);

    /*�������� StopVMP
    ��    �ܣ� ֹͣ��Ƶ����
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 StopVMP();
    
    /*�������� UpdateVMP
    ��    �ܣ� �޸���Ƶ���ϲ���
    ��    ���� const TMtVMPParam &vmp
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 UpdateVMP(const TMtVMPParam &vmp);
    
    
    /*�������� ChangeVmpType
    ��    �ܣ� �޸���Ƶ���ϲ���
    ��    ���� u8 byIndex  ������� ��0��ʼ
               u8 byType   ��������
                                                0  //Ϊ�ر�
               VMP_MEMBERTYPE_MCSSPEC           1  //���ָ�� 
               VMP_MEMBERTYPE_SPEAKER           2  //�����˸���
               VMP_MEMBERTYPE_CHAIRMAN          3  //��ϯ����
               VMP_MEMBERTYPE_POLL              4  //��ѯ��Ƶ����
    �� �� ֵ�� BOOL3232 
    ˵    ���� */
	BOOL32 ChangeVmpType(u8 byIndex, u8 byType);
    
    /*�������� DynSwitchVmpStyle
    ��    �ܣ� �޸���Ƶ���Ϸ��
    ��    ���� u8 byType :���(VMP_STYLE_DYNAMIC��)
    �� �� ֵ�� 
    ˵    ���� */
    BOOL32 DynSwitchVmpStyle(u8 byType);

    /*�������� SelectMt
    ��    �ܣ� ѡ���ն�
    ��    ���� CString &szMt 
               u8 byTypeѡ������
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 SelectMt(const CString& szMt, u8 byType);

    /*�������� CancelSelectMT
    ��    �ܣ� ȡ��ѡ��
    ��    ���� CString &szMt
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 CancelSelectMT(const CString& szMt);
    
    /*�������� StartPoll
    ��    �ܣ� ��ʼ������ѯ
    ��    ���� u32 dwInterval ��ѯ���
               u8 byType      ��ѯ����
               vector<CString> &vctMt��ѯ�ն�
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 StartPoll(u32 dwInterval, u8 byType, vector<CString> &vctMt);

    /*�������� StopPoll
    ��    �ܣ� ֹͣ������ѯ
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 StopPoll();

    /*�������� PausePoll
    ��    �ܣ� ��ͣ������ѯ
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 PausePoll();
	
    /*�������� ResumePoll
    ��    �ܣ� �ָ�������ѯ
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 ResumePoll();

    /*�������� SendShortMessage
    ��    �ܣ� ������ն˷��Ͷ���Ϣ
    ��    ���� vector<CString> &vctMt �����ն�
               CString szMsg ��Ϣ����
               BOOL32 bSelectAll ȫѡ
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 SendShortMessage(const CString& vctMt, const CString& szMsg,
                            BOOL32 bSelectAll = FALSE);
	
    /*�������� BroadcastMessage
    ��    �ܣ� ������ն˹㲥��Ϣ
    ��    ���� CString& vctMt �����ն�
               CString& szMsg ��Ϣ����
               BOOL32 bSelectAll ȫѡ
			   u32 dwTimes ���ʹ���
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 BroadcastMessage(vector<CString> &vctMt, const CString& szMsg,
                            BOOL32 bSelectAll = FALSE, u32 dwTimes = 1);

    /*�������� AcceptMt
    ��    �ܣ� �����ն����� �����������ն����뷢�ԡ���ϯ���廰ʱ�����Ի����ȷ��
    ��    ���� CString szMtName �ն�����
               BOOL32 bAccept  TRUE����, FALSE�ܾ�
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 AcceptMt(const CString& szMtName, BOOL32 bAccept = TRUE);
    
    /*�������� RemoteDummy
    ��    �ܣ� Զ������
    ��    ���� CString szMt
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 RemoteDummy(const CString& szMt);

    /*�������� RemoteSilent
    ��    �ܣ� Զ�˾���
    ��    ���� CString szMt
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 RemoteSilent(const CString& szMt);


    //************�ն�����************************************************// 

    /*�������� SetCfgPassword
    ��    �ܣ� �������ÿ���
    ��    ���� String& szNewPassword: Ϊ��ʱ��ʾȡ������
               String& szOldPassword: �ɿ���
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 SetCfgPassword(const CString& szNewPassword = _T(""), 
		                  const CString& szOldPassword = _T(""));
    
    /*�������� UpdateCfgLocal
    ��    �ܣ� ��������
    ��    ���� const TH323Cfg &rCfg
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 UpdateCfgLocal(const TH323Cfg &rCfg, const CString& szPassword = _T(""));

    /*�������� UpdateCfgOSD
    ��    �ܣ� ̨������
    ��    ���� const TOsdCfg *tCfg
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 UpdateCfgOSD(const TOsdCfg &rCfg, const CString& szPassword = _T(""));

    /*�������� ChangeSign
    ��    �ܣ� ����̨��
    ��    ���� CString szBMPPath ̨���ļ���ȫ·��
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 ChangeSign(const CString& szBMPPath);

    /*�������� UpdateCfgNet
    ��    �ܣ� ��������
    ��    ���� const TEthnetInfo &rCfg
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 UpdateCfgNet(const TEthnetInfo &rCfg, const CString& szPassword = _T(""));

    /*�������� SetOtherCfg
    ��    �ܣ� ��������
    ��    ���� const TOtherCfg& tCfg
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 SetOtherCfg(const TOTHERCFG& tCfg, const CString& szPassword = _T(""));

    /*�������� UpdateCfgSnmp
    ��    �ܣ� SNMP����
    ��    ���� const TSNMPCfg &tCfg
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 UpdateCfgSnmp(const TSNMPCfg &tCfg, const CString& szPassword = _T(""));

    /*�������� UpdateCfgCall
    ��    �ܣ� ��������
    ��    ���� const TUserCfg &rCfg
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 UpdateCfgCall(const TUserCfg &rCfg, const CString& szPassword = _T(""));

    /*�������� UpdateCfgVEnc
    ��    �ܣ� ��Ƶ��������
    ��    ���� const TVideoParam &rCfg
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 UpdateCfgVEnc(const TVideoParam &rCfg, const CString& szPassword = _T(""));

    /*�������� UpdateCfgAVProtocol
    ��    �ܣ� ��Ƶ��������
    ��    ���� const TAVPriorStrategy &rCfg
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 UpdateCfgAVProtocol(const TAVPriorStrategy &rCfg, const CString& szPassword = _T(""));

    /*�������� UpdateCfgAVProtocol
    ��    �ܣ� ��Ƶ��������
    ��    ���� const TVideoParam &rCfg
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 UpdateCfgH264(const TVideoParam &rCfg, const CString& szPassword = _T(""));

    /*�������� UpdateCfgVCap
    ��    �ܣ� ��Ƶ�ɼ�����
    ��    ���� const _TPCCODEC &rCfg
    �� �� ֵ�� BOOL32 
    ˵    ���� */
//	BOOL32 UpdateCfgVCap(const _TPCCODEC &rCfg, const CString& szPassword = _T(""));

    /*�������� UpdateCfgSendRt
    ��    �ܣ� �����ش�����
    ��    ���� const TRetransCfg &rCfg
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 UpdateCfgSendRt(const TLostPackResend &rCfg, const CString& szPassword = _T(""));

    /*�������� UpdateCfgPanel
    ��    �ܣ� ������ý������
    ��    ���� const TStreamMedia &tCfg
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 UpdateCfgPanel(const TStreamMedia &tCfg, const CString& szPassword = _T(""));

       /*************ϵͳ���ӿ�*****************/
	/*�������� SelfLoop
    ��    �ܣ� �Ի�
    ��    ���� BOOL32 bStart TRUE ��ʼ,FALSE ֹͣ
    �� �� ֵ�� BOOL32 �ɹ�����TRUE��ʧ�ܷ���FALSE
    ˵    ���� */
	BOOL32 SelfLoop(BOOL32 bStart);


	/********************��ַ������****************************************************/
    /*�������� AddEntry
    ��    �ܣ� ������Ŀ
    ��    ���� CString &szEntryName ��Ŀ����
               u32 dwIP ������IP��ַ
               CString &szAlias
               CString &szE164
               u16 wBitRate
    �� �� ֵ�� BOOL32 �ɹ�����TRUE��ʧ�ܷ���FALSE
    ˵    ���� */
	BOOL32 AddEntry(const CString &szEntryName, u32 dwIP,const CString &szAlias,
		            const CString &szE164, u16 wBitRate);

    /*�������� ModifyEntry
    ��    �ܣ� �޸���Ŀ
    ��    ���� CString &szOldEntryName ԭ��������
               CString &szEntryName    �޸ĺ������
               DWORD dwIP
               CString &szAlias
               CString &szE164
               u16 wBitRate
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 ModifyEntry(const CString &szOldEntryName,const  CString &szEntryName, 
		               DWORD dwIP, const CString &szAlias,const  CString &szE164, 
					   u16 wBitRate);
	 
    /*�������� DeleteEntry
    ��    �ܣ� ɾ����Ŀ
    ��    ���� CString &szEntryName ��Ŀ����
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 DeleteEntry(const CString &szEntryName);

    /*�������� AddGroup
    ��    �ܣ� ������
    ��    ���� CString &szGroupName  ����
               DWORD dwIP IP
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 AddGroup(const CString &szGroupName, DWORD dwIP);

    /*�������� ModifyGroup
    ��    �ܣ� �޸���
    ��    ���� CString &szOldGroupName ԭ��������
               CString &szGroupName    �޸ĺ������
               DWORD dwIP
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 ModifyGroup(const CString &szOldGroupName, const CString &szGroupName, DWORD dwIP);

    /*�������� DeleteGroup
    ��    �ܣ� ɾ����
    ��    ���� CString szGroupName
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 DeleteGroup(const CString &szGroupName);

    /*�������� AddEntryToGroup
    ��    �ܣ� �����Ŀ����
    ��    ���� CString &szGroupName
               vector<CString> vctAddrEntry
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 AddEntryToGroup(const CString &szGroupName, vector<CString>& vctAddrEntry);

    /*�������� DelEntryFromGroup
    ��    �ܣ� ����ɾ����Ŀ
    ��    ���� CString &szGroupName 
               vector<CString> vctAddrEntry ��Ŀ��
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 DelEntryFromGroup(const CString &szGroupName, vector<CString>& vctAddrEntry);

    /*�������� ClearEntry
    ��    �ܣ� �����Ŀ
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 ClearEntry();

    /*�������� ClearGroup
    ��    �ܣ� ��ջ�����
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 ClearGroup();

    /*�������� ModulateEncVolume
    ��    ��   �����������
    ��    ��   u32 dwVolume ���ں������
    �� �� ֵ   BOOL32
	˵    ��   */
	BOOL32 ModulateEncVolume(u32 dwVolume);

    /*�������� ModulateDecVolume
    ��    ��   ������������
    ��    ��   u32 dwVolume ���ں������
    �� �� ֵ   BOOL32
	˵    ��   */
	BOOL32 ModulateDecVolume(u32 dwVolume);

    //************���ݻ�������ӿ�************************************************// 

    /*�������� DCCreateConf
    ��    ��   �������ݻ���
    ��    ��   szConfName��         ���������
			   szConfPwd :          �������루û������ʱ������ΪNULL����""��
			   bAppShareDisable:    ����������Ƿ��ֹ��������
               bWhiteBoardDisable�� ����������Ƿ��ֹ�����װ�
               bFileTransDisable:   ����������Ƿ��ֹ�����ļ�����
               bChatDisable:        ����������Ƿ��ֹ��������
    �� �� ֵ   BOOL32
			   TRUE��  �ɹ����ֻ��� 
			   FALSE�� ʧ��
	˵    ��   */      
	BOOL32 DCCreateConf(const CString& szConfName, 
						const CString& szConfPwd, 
						BOOL32 bAppShareDisable,
						BOOL32 bWhiteBoardDisable, 
						BOOL32 bFileTransDisable, 
						BOOL32 bChatDisable);

    /*�������� DCCall
    ��    ��   ���ݻ������
    ��    ��   const CString& szIPAddress �����ն˵�IP��ַ
    �� �� ֵ   BOOL32
	˵    ��   */
	BOOL32 DCCall( const CString& szIPAddress );

	/*�������� DCEjectMt
    ��    ��   ���ݻ��������ն�
    ��    ��   const CString& szIPAddress Ҫ���˵��ն˵�IP��ַ
    �� �� ֵ   BOOL32
	˵    ��   */
	BOOL32 DCEjectMt (const CString& szMtName);

	/*�������� DCJoinReqConfirm
    ��    ��   �������ȷ��
    ��    ��   const CString& szMtName ���������ն�����
			   BOOL32 bAccept �Ƿ����
    �� �� ֵ   BOOL32
	˵    ��   */
	BOOL32 DCJoinReqConfirm(const CString& szMtName, BOOL32 bAccept);

	/*�������� DCInviteReqConfirm
    ��    ��   �������ȷ��
    ��    ��   const CString& szMtName ����������ն�����
			   BOOL32 bAccept �Ƿ����
    �� �� ֵ   BOOL32
	˵    ��   */
	BOOL32 DCInviteReqConfirm(const CString& szMtName, BOOL32 bAccept);

	/*�������� DCJoinConf
    ��    ��   ��������ȷ��
    ��    ��   const CString& szConfName ��������
			   const CString& szConfPwd ��������
    �� �� ֵ   BOOL32
	˵    ��   */
	BOOL32 DCJoinConf (const CString& szConfName, const CString& szConfPwd);

	/*�������� DCInputConfPwd
    ��    ��   �������
    ��    ��   const CString& szConfPwd ��������
    �� �� ֵ   BOOL32
	˵    ��   */
	BOOL32 DCInputConfPwd (const CString& lpszConfPwd);
	
	/*�������� DCLeaveConf
    ��    ��   �˳�����
    ��    ��   ��
    �� �� ֵ   BOOL32
	˵    ��   ����Ǳ��ն˴����Ļ��飬��������λ���*/
	BOOL32 DCLeaveConf();

	/*�������� DCStartShare
    ��    ��   ����������
    ��    ��   ��
    �� �� ֵ   BOOL32
	˵    ��   */
	BOOL32 DCStartShare();

	/*�������� DCSwitchShareWindow
    ��    ��   �л���������
    ��    ��   ��
    �� �� ֵ   BOOL32
	˵    ��   */
	BOOL32 DCSwitchShareWindow();

	/*�������� DCStartWhiteBoard
    ��    ��   �����װ�Ӧ��
    ��    ��   ��
    �� �� ֵ   BOOL32
	˵    ��   */
	BOOL32 DCStartWhiteBoard();

	/*�������� DCSwitchWhiteBoardWindow();
    ��    ��   �л����װ崰��
    ��    ��   ��
    �� �� ֵ   BOOL32
	˵    ��   */
	BOOL32 DCSwitchWhiteBoardWindow ();

	/*�������� DCStartFileTransfer
    ��    ��   �����ļ�����
    ��    ��   ��
    �� �� ֵ   BOOL32
	˵    ��   */
	BOOL32 DCStartFileTransfer();

	/*�������� DCStartChat
    ��    ��   ��������
    ��    ��   ��
    �� �� ֵ   BOOL32
	˵    ��   */
	BOOL32 DCStartChat();

	/*�������� DCStopChat
    ��    ��   �ر�����
    ��    ��   ��
    �� �� ֵ   BOOL32
	˵    ��   */
	BOOL32 DCStopChat();

	/*�������� DCSendPublicChatMsg
    ��    ��   ���͹�����Ϣ
    ��    ��   const CString& szMsg ��Ϣ����
    �� �� ֵ   BOOL32
	˵    ��   */
	BOOL32 DCSendPublicChatMsg (const CString& szMsg);

	/*�������� DCSendPrivateChatMsg
    ��    ��   ����˽����Ϣ
    ��    ��   const CString& szMtName Ŀ���ն�
			   const CString& szMsg ��Ϣ����
    �� �� ֵ   BOOL32
	˵    ��   */
	BOOL32 DCSendPrivateChatMsg(const CString& szMtName, const CString& szMsg);

	/*�������� DCSetConfigInfo
    ��    ��   �������ò���
    ��    ��   szDefaultFileReceivePath    �ļ���������ļ���ȱʡ����·��
               szDefaultHostConfName       �Զ���������ʱ�����������ȱʡ����
               bDefaultStartColorShare     ��������ʱȱʡ�Ƿ����ɫ����
    �� �� ֵ   BOOL32
	˵    ��   */
	BOOL32 DCSetConfigInfo(const CString& szDefaultFileReceivePath,
						   const CString& szDefaultHostConfName,
						   BOOL32 bDefaultStartColorShare);

	/*�������� DCSetMaxBandwidth
    ��    ��   �����ն��������(����)
    ��    ��   u32 dwBandwidth ����
    �� �� ֵ   BOOL32
	˵    ��   */
	BOOL32 DCSetMaxBandwidth(u32 dwBandwidth);
	
	/*�������� DCSwitchLanguage
    ��    ��   ��Ӣ���л�
    ��    ��   u8 byType 0 ���� 1 Ӣ��
    �� �� ֵ   BOOL32
	˵    ��   */
	BOOL32 DCSwitchLanguage(u8 byType);

private:
	inline void SLEEP(u32 dwSeconds)
	{
		if(m_bDelay)
		{
			::Sleep(dwSeconds);
		}
	}

private:	
    CGuiUnit			m_cGuiUnit;   //��������ӿ������
    BOOL32              m_bResult;    //����������
    HWND                m_hWndIE;     //IE�����������ھ��

private:
    u8                  m_byUIIndex;
    BOOL32              m_bDelay;
private:
    HWND                m_hMainFrame;

	HWND                m_hBtnApplyChairman;
	HWND                m_hBtnApplySpeaker;
	HWND                m_hBtnApplyChime;

    //button
    HWND                m_hBtnHelp;
    HWND                m_hBtnMonitor;
    HWND                m_hBtnAddressBook;
	
	//local & remote video
	HWND                m_hLocalVideo;
	HWND                m_hRemoteVideo;

    //��ģ��
	HWND                m_hTab;
    HWND                m_hBroadCastWnd;
    HWND                m_hSimRoomWnd;
    HWND                m_hDCShareWnd;
    HWND                m_hDCWhiteBoardWnd;
    HWND                m_hSMS;
    HWND                m_hMonitorPanel;
    HWND                m_hAddressbook;

    //p2p
    HWND                m_hBtnCall;
    HWND                m_hP2PAddress;

    //conflist
    HWND                m_hBtnCreate;
    HWND                m_hBtnEnd;
    HWND                m_hBtnJoin;
    HWND                m_hBtnInvite;
    HWND                m_hMtlist;

    HWND                m_hConfig;
    HWND                m_hStatistic;
    HWND                m_hFullScreen;
    HWND                m_hSnapshot;
    HWND                m_hSelfTest;
    HWND                m_hMute;
    HWND                m_hSilent;
    HWND                m_hPlayVol;
    HWND                m_hCaptureVol;
    HWND                m_hPlayWnd;

    //simroom
    HWND                m_hListPlatform;
    HWND                m_hListAudience;

    //short message
    HWND                m_hBtnSend;
    HWND                m_hComboMt;
    HWND                m_hEditMessage;
    HWND                m_hEditDisplay;

    //monitor dialog
    HWND                m_hSource1;
    HWND                m_hSource2;

    //monitor panel
    HWND                m_hMonitorWnd[9];
    HWND                m_hBtnMonitorStyle[6];
};

#endif