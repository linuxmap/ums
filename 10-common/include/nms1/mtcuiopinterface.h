/*****************************************************************************
  ģ����      : �ܵĲ����ӿ�
  �ļ���      : MtcUIOPInterface.h
  ����ļ�    : 
  �ļ�ʵ�ֹ���: ��Ԫ����
  ����        : �����
  �汾        : V3.5  Copyright(C) 1997-2005 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2004/11/9   3.5         �����      ����
******************************************************************************/
#if !defined(AFX_UIOPINTERFACE_H__57F5B3B1_71A8_4327_8ADC_7BB80C75C02F__INCLUDED_)
#define AFX_UIOPINTERFACE_H__57F5B3B1_71A8_4327_8ADC_7BB80C75C02F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//����ӿ�
#include "cppunit\GuiUnit.h"

#include <vector>

#include "kdvType.h"		// ��������
#include "kdvDef.h"			// ������
#include "osp.h"			// OSPҵ��
#include "tpstruct.h"		// �ն˿���ҵ��
#include "ummessagestruct.h"// �����֤ҵ��

#include "AddrBook.h"

#define DELAYTIME 500

#define MTCUILIBASSERT(bRet)            \
    {                                   \
        if (bRet == FALSE) return FALSE;\
    }

#define MTCUIHWNDASSERT(hWnd)           \
    {                                   \
        if (hWnd == NULL) return FALSE; \
    }


using namespace std;
typedef struct tagMtConfigInfo
{
	CString strName;
	CString strIP;
	CString strLocalAddr;
}TMtConfigInfo;

//�ܵĲ����ӿ�
class CMtcUIOPInterface  
{
	
public:
	enum 
	{
		emBannerOne = 0, 
		emBannerTwo
	};

    CMtcUIOPInterface();
	virtual ~CMtcUIOPInterface();	

protected:
    //*****�ڲ��õĲ����ӿ�************************************************************//
    /*�������� GuiActiveWindow
    ��    �ܣ� �����ն˿���̨����
    ��    ���� 
    �� �� ֵ�� BOOL �ɹ�����TRUE��ʧ�ܷ���FALSE
    ˵    ���� */
    BOOL32 GuiActiveWindow(); 

    /*�������� MoveToBtn
    ��    �ܣ� �ƶ��������������ĳ����ť
    ��    ���� HWND hWnd ��ť���
    �� �� ֵ�� BOOL �Ƿ�ɹ�
    ˵    ���� */
    BOOL32 MoveToBtn(HWND hWnd); 
	
	/*�������� MovetoTextInput
    ��    �ܣ� �ƶ�����Text�ؼ�����������
    ��    ���� HWND hWnd ��ť���
    �� �� ֵ�� BOOL �Ƿ�ɹ�
    ˵    ���� */
	BOOL32 MovetoTextInput(const CString &cs, HWND hWnd)
	{
		m_cGuiUnit.MouseMove(hWnd);
		m_cGuiUnit.TextInput(cs, hWnd);
		Sleep(DELAYTIME);
		return TRUE;
	}
	/*�������� SpecialDeal
    ��    �ܣ� �쳣����
    ��    ���� HWND hWnd ��ť���
    �� �� ֵ�� BOOL �Ƿ�ɹ�
    ˵    ���� */
	BOOL32 SpecialDeal()
	{
		HWND hPopEx = m_cGuiUnit.GetPopWindow();
		if (hPopEx != NULL)
		{
			HWND hWnd = m_cGuiUnit.GetHWnd(hPopEx, IDOK);
			MoveToBtn(hWnd);
			return FALSE;
		}
		return TRUE;
	}

    /*�������� InitMtcHandle
    ��    �ܣ� ��ʼ�����
    ��    ���� 
    �� �� ֵ�� BOOL 
    ˵    ���� */
    BOOL32 InitMtcHandle();    

    /*�������� IsInP2PConf
    ��    �ܣ� �Ƿ��ڵ�Ե�����У������ں�����
    ��    ���� 
    �� �� ֵ�� BOOL 
    ˵    ���� */
    BOOL32 IsInP2PConf();

    /*�������� IsInMultiConf
    ��    �ܣ� �Ƿ��ڶ�������
    ��    ���� 
    �� �� ֵ�� BOOL 
    ˵    ���� */
    BOOL32 IsInMultiConf();

	/*�������� IsInConf
    ��    �ܣ� �Ƿ��ڻ�����
    ��    ���� 
    �� �� ֵ�� BOOL 
    ˵    ���� */
    BOOL32 IsInConf();

    /*�������� IsChairMan
    ��    �ܣ� �Ƿ���ϯ
    ��    ���� 
    �� �� ֵ�� bool 
    ˵    ���� */
	BOOL32 IsChairMan();

    /*�������� IsSpeaker
    ��    �ܣ� �Ƿ�����
    ��    ���� 
    �� �� ֵ�� bool 
    ˵    ���� */
	BOOL32 IsSpeaker();

    /*�������� GetConnectMt
    ��    �ܣ� ��õ�ǰ�����ŵ��ն˵ı���
    ��    ���� 
    �� �� ֵ�� CString 
    ˵    ���� */
    CString GetConnectMt();

    /*�������� GetSpeaker
    ��    �ܣ� 
    ��    ���� CString &strSpeaker
    �� �� ֵ�� 
    ˵    ���� */
    CString GetSpeaker();

    /*�������� GetChairman
    ��    �ܣ� 
    ��    ���� CString &strChairman
    �� �� ֵ��  
    ˵    ���� */
    CString GetChairman();

    /*�������� SwitchSheet
    ��    �ܣ� �л�����ǰsheet
    ��    ���� int nCurSheet
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 SwitchSheet(INT nCurSheet);

    /*�������� GetCurSheet
    ��    �ܣ� �õ���ǰ��sheet
    ��    ���� 
    �� �� ֵ�� INT 
    ˵    ���� */
    INT GetCurSheet();
    /*�������� ConfigE1Module
    ��    �ܣ� ����һ��E1ģ��
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 ConfigE1Module(const TE1Unit& tE1Module);
	/*�������� ComboxSelect
    ��    �ܣ� �����б��ѡȡ
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 ComboxSelect(HWND hWnd, u32 dwData);
	/*�������� ComboxSelect
    ��    �ܣ� �����б��ѡȡ
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 ComboxSelect(HWND hWnd, CString csData);

	/*�������� MoveToCheck
    ��    �ܣ� �Ƶ���ѡ�򲢵���
    ��    ���� 
    �� �� ֵ�� void 
    ˵    ���� */
	void MoveToCheck(HWND hWnd, BOOL32 bCheck)
	{
		if (IsWindowEnabled(hWnd))
		{
			if (bCheck != m_cGuiUnit.ButtonGetCheck(hWnd))
			{
				MoveToBtn(hWnd);
				Sleep(DELAYTIME);
			}
		}
	}
	/*�������� TextInPut
    ��    �ܣ� �ڱ༭����������
    ��    ���� 
    �� �� ֵ�� void 
    ˵    ���� */
	void TextInPut(HWND hWnd, CString csIn)
	{
		if (::IsWindowEnabled(hWnd))
		{
			CString csGet;
			m_cGuiUnit.TextGet(csGet, hWnd);
			if (strcmp(csGet, csIn)) 
			{
				m_cGuiUnit.MouseMove(hWnd);
				Sleep(DELAYTIME);
				m_cGuiUnit.TextInput(csIn, hWnd);
				Sleep(DELAYTIME);
			}
		}
		
	}
	/*�������� TextInPut
    ��    �ܣ� �ڱ༭����������
    ��    ���� 
    �� �� ֵ�� void 
    ˵    ���� */
	void TextInPut(HWND hWnd, u32 dwData)
	{
		CString csIn;
		csIn.Format(_T("%d"), dwData);
		TextInPut(hWnd, csIn);
	}
	/*�������� SetIpAddr
    ��    �ܣ� ����IP��ַ
    ��    ���� 
    �� �� ֵ�� void 
    ˵    ���� */
	void SetIpAddr(HWND hWnd, u32 dwIp)
	{
		if (::IsWindowEnabled(hWnd))
		{
			u32 dwGetIP = 0;
			m_cGuiUnit.IpAddressGet(&dwGetIP, hWnd);
			if (dwGetIP != dwIp)
			{
				m_cGuiUnit.MouseMove(hWnd);
				Sleep(DELAYTIME);
				m_cGuiUnit.IpAddressSet(dwIp, hWnd);
				Sleep(DELAYTIME);
			}
		}
	}
	/*�������� ConfigApply
    ��    �ܣ� ������ҳ���Ӧ��
    ��    ���� 
    �� �� ֵ�� BOOL32
    ˵    ���� */
	BOOL32 ConfigApply()
	{
		HWND hWnd = m_cGuiUnit.GetHWnd(20041, CBUTTON, 448);
		MTCUIHWNDASSERT(hWnd);
		MoveToBtn(hWnd);
		Sleep(DELAYTIME);
		return TRUE;
	}

	/*�������� SetSliderPos
    ��    �ܣ� ����slide�ؼ���λ��
    ��    ���� 
    �� �� ֵ�� BOOL32
    ˵    ���� */
	void SetSliderPos(HWND hWnd, s32 nPos)
	{
		s32 nGetPos;
		m_cGuiUnit.SliderGetPos(&nGetPos, hWnd);
		if (nGetPos != nPos)
		{
			m_cGuiUnit.MouseMove(hWnd);
			Sleep(DELAYTIME);
			m_cGuiUnit.SliderSetPos(nPos, hWnd);
			Sleep(DELAYTIME);
		}
	}
public:
    //*****�ṩ���ⲿ���õĽӿ�******//

    //*****ϵͳ��ʼ���Ĳ����ӿ�********************************************************//
   
    /*�������� GuiInit
    ��    �ܣ� ��ʼ��MTC
    ��    ���� CString strExePath   ����·��
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 GuiInit(CString strExePath);
	
    /*�������� LoginMt
    ��    �ܣ� ��¼�ն�
    ��    ���� CString szMtIP       Ҫ���ӵ��ն�IP
               CString strLoginName �����û���
               CString strLoginPwd  ��������
               BOOL32  bNeverSleep  �Ƿ������������״̬
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 LoginMt(const CString& szMtIP,const CString& strLoginName = _T("admin"),
		const CString& strLoginPwd  = _T("admin"),BOOL32 bNeverSleep = TRUE);
    
	/*�������� InitOP
    ��    �ܣ� �ٴγ�ʼ�������
    ��    ���� CString strTitle ��������
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 InitOP(CString strTitle);
    
    /*�������� LoginMtc
    ��    �ܣ� �����տ�
    ��    ���� CString strLoginName  �û���
               CString strLoginPwd   �û�����
    �� �� ֵ�� BOOL32 
    ˵    ���� */
 	BOOL32 LoginMtc(CString strLoginName, CString strLoginPwd);
    
    /*�������� Refresh
    ��    �ܣ� ��ˢ���棬�Ա����µ�½
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 Refresh();

    /*�������� close
    ��    �ܣ� �رղ��Խӿ������ֳ�
    ��    ���� 
    �� �� ֵ�� void 
    ˵    ���� �˳�ʱ��õ����Ա�رղ��Զ���*/
    void Close();

    /*�������� IsConnected
    ��    �ܣ� �Ƿ��Ѿ������ն�
    ��    ���� 
    �� �� ֵ�� BOOL 
    ˵    ���� */
    BOOL IsConnected(); 
    
    //**********��������Խӿ�********************************************************//

    //ͷ����ť����
    /*�������� AboutVer
    ��    �ܣ� ���ڰ汾��Ϣ
    ��    ���� 
    �� �� ֵ�� 
    ˵    ���� */
    BOOL AboutVer();

    /*�������� AboutHelp
    ��    �ܣ� ���ڰ���
    ��    ���� 
    �� �� ֵ�� 
    ˵    ���� */
    BOOL AboutHelp();

    /*�������� TerminalSnapshot
    ��    �ܣ� �ն˿���
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 TerminalSnapshot();

    /*�������� ClearMtSnapshot
    ��    �ܣ� ����ն��ϵĿ���
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 ClearMtSnapshot();

    /*�������� DeleteMtSnapshot
    ��    �ܣ� ɾ��һ���ն��ϵĿ���
    ��    ���� s32 nItem ��������
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 DeleteMtSnapshot(s32 nItem);

    /*�������� AddrbookShow
    ��    �ܣ� ��ַ������
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 AddrbookShow();
	
     /*�������� DualStream
    ��    �ܣ� ˫��
    ��    ���� s32 nType = ˫������ 0��2 λ����˫������ ��1δֹͣ˫��
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 DualStream(s32 nType = 0);
	
	/*�������� StopDualStream
    ��    �ܣ� ˫��
    ��    ���� s32 nType = ˫������ 0��2 λ����˫������ ��1δֹͣ˫��
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 StopStream();

    /*�������� Reset
    ��    �ܣ� ��λ
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 Reset();

    /*�������� SleepMt
    ��    �ܣ� ����
    ��    ���� DWORD dwType �������� 0 ���� 1��60���ֺ� 2��120���ֺ�
                                            3��180���ֺ� 4���������� 
               BOOL32 bSleep = TRUE �Ƿ�����
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 SleepMt(DWORD dwType= 0, BOOL32 bSleep = TRUE);

    /*�������� LocalMonitor
    ��    �ܣ� ���ؼ��
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 LocalMonitor();

    /*�������� Dummy
    ��    �ܣ� ����
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 Dummy();

    /*�������� Silent
    ��    �ܣ� ����
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 Silent();

    /*�������� RemoteMonitor
    ��    �ܣ� Զ�˼��
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 RemoteMonitor();

    /*�������� LocalFullScreen
    ��    �ܣ� ����ȫ��
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 LocalFullScreen();

    /*�������� RemoteFullScreen
    ��    �ܣ� Զ��ȫ��
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 RemoteFullScreen();

    /*�������� RemoteSnap
    ��    �ܣ� Զ��ץ��
    ��    ���� CString strPath=_T("") ����·��������Ļ����浽Ĭ��·��
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 RemoteSnap(CString strPath=_T(""));

    /*�������� LocalSnap
    ��    �ܣ� Զ��ץ��
    ��    ���� CString strPath=_T("") ����·��������Ļ����浽Ĭ��·��
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 LocalSnap(CString strPath=_T(""));

    //************��Ե�������*****************************************************// 
    
    /*�������� CallbyMT()
    ��    �ܣ� ͨ����ַ��Ŀ���������ն�
    ��    ���� TMtAddr tTermAddr �ն˺��нṹ 
				u16               wBitRate ��������
               BOOL32 bAddrbook  TRUE ͨ����ַ�������� 
			   DWORD dwSleepTime ���ߵȴ�ʱ��,�������ʱ�䲻Ϊ0������ж��Ƿ�����˻���
    �� �� ֵ�� BOOL32 �ɹ�����TRUE��ʧ�ܷ���FALSE
    ˵    ���� */
	BOOL32 CallbyMT(TMtAddr tTermAddr, u16 wBitRate, BOOL32 bAddrbook = FALSE, DWORD dwSleepTime=15000);
	
    
    /*�������� CallbyMTEx()
    ��    �ܣ� ͨ����ַ��Ŀ���������ն�
    ��    ���� TMtAddr tTermAddr �ն˺��нṹ u16 
               wBitRate ��������
               BOOL32 bAddrbook  TRUE ͨ����ַ�������� 
    �� �� ֵ�� BOOL32 �ɹ�����TRUE��ʧ�ܷ���FALSE
    ˵    ���� */
	BOOL32 CallbyMTEx(TMtAddr tTermAddr, u16 wBitRate, BOOL32 bAddrbook = FALSE);

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
    ��    ���� u32 dwMcuIp					[in]Mcu��Ip��ַ
			   const TConfBaseInfo &info			[in]������Ϣ
			   const vector<TMtAddr>& vMts	[in]�ն���Ϣ
               CString strGroupName = "" ����Ŀ����
               BOOL32 bByAddrbook ͨ����ַ��
			   DWORD dwSleepTime ���ߵȴ�ʱ�䣬Ĭ��ֵΪ20��
    �� �� ֵ�� BOOL32 �ɹ�����TRUE��ʧ�ܷ���FALSE
    ˵    ���� */
	BOOL32 CreateConf(u32 dwMcuIp, CString csBitrate,
        const TConfBaseInfo &info, const vector<TMtAddr>& vMts,
        CString strGroupName = "", BOOL32 bByAddrbook = FALSE); 

   BOOL32 CreateConf(TMtAddr tMcuInfo, CString u16Bitrate,
   const  TConfBaseInfo &info, const vector<TMtAddr>& vMts,
   CString strGroupName = "", BOOL32 bByAddrbook = FALSE, DWORD dwSleepTime=20000); 
   
   //���ȴ���Ӧ�ͷ���
   BOOL32 CreateConfEx(TMtAddr tMcuInfo, CString u16Bitrate,
   const TConfBaseInfo &info, const vector<TMtAddr>& vMts,
   CString strGroupName = "", BOOL32 bByAddrbook = FALSE);

    /*�������� JoinConf
    ��    �ܣ� �ն�����������
    ��    ���� const TMtAddr& mcu [in]MCU�ĵ�ַ
               u16 &wBitRate ��������
               CString strConfName ��������
               CString strPWD ��������
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 JoinConf(const TMtAddr& mcu, u16 &wBitRate,
                    CString strConfName=_T(""), CString strPWD = "123");

    /*�������� SelectConf
    ��    �ܣ� 
    ��    ���� char *ConfName
    �� �� ֵ�� BOOL32 
    ˵    ���� */

	BOOL32 SelectConf(CString strConfName);
	/*�������� InputConfPass
    ��    �ܣ� 
    ��    ���� char *strPass
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 InputConfPass(char *strPass);		
	
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
    /*�������� InviteMt
    ��    �ܣ� �����ն�
    ��    ���� const TMtAddr& tMt
               u16 &wBitRate
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 InviteMt(const TMtAddr& tMt, u16 &wBitRate);

    /*�������� RevokeMt
    ��    �ܣ� �����ն�
    ��    ���� CString &szMt
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 RevokeMt(CString &szMt);

    /*�������� AcceptInvite
    ��    �ܣ� ��������
    ��    ���� BOOL32 bAccepted == TRUE ���� FALSE �ܾ�
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 AcceptInvite(BOOL32 bAccepted = TRUE);

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
	BOOL32 SpecifySpeaker(CString &szMt);

    /*�������� SpecifyChairman
    ��    �ܣ� ָ����ϯ�ն�
    ��    ���� CString &szMt
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 SpecifyChairman(CString &szMt);

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

    /*�������� ���ڻ��л�����/�رպ�λ���ƶ�
    ��    �ܣ� 
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 PipMove();
    /*��������  ���л��Ĵ�С���滥��
    ��    �ܣ� 
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 PipSwitch();
	/*�������� StartDiscuss
    ��    �ܣ� ��ʼ����ģʽ
    ��    ���� int u8Max ���۵����
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 StartDiscuss(int u8Max);

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
    ��    ���� u8 nType �������� ���δ0�Ļ������Զ�����
               vector<CString> &vctMT ���븴�ϵ��ն�
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 StartVMP(u8 nType, vector<CString> &vctMt);

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

 
    /*�������� ChangeVMPMember
    ��    �ܣ� �޸���Ƶ���ϲ���
    ��    ���� int nIndex  ������� ��0��ʼ
               int nType   ���ϳ�Ա����
               0, Ϊ�ر�
               VMP_MEMBERTYPE_MCSSPEC           1  //���ָ�� 
               VMP_MEMBERTYPE_SPEAKER           2  //�����˸���
               VMP_MEMBERTYPE_CHAIRMAN          3  //��ϯ����
               VMP_MEMBERTYPE_POLL              4  //��ѯ��Ƶ����
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 ChangeVMPMember(int nIndex, int nType);

    /*�������� SelectMt
    ��    �ܣ� ѡ���ն�
    ��    ���� CString &strMt 
               INT nTypeѡ������
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 SelectMt(CString &strMt, INT nType);

    /*�������� CancelSelectMT
    ��    �ܣ� ȡ��ѡ��
    ��    ���� CString &strMt
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 CancelSelectMT(CString &strMt);
    
    /*�������� StartPoll
    ��    �ܣ� ��ʼ��ѯ
    ��    ���� INT nInterval ��ѯ���
               INT nType     ��ѯ����
               vector<CString> &vctMt��ѯ�ն�
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 StartPoll(u8 byInterval, u8 byType, vector<CString> &vctMt);

    /*�������� StopPoll
    ��    �ܣ� ֹͣ��ѯ
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 StopPoll();

    /*�������� PausePoll
    ��    �ܣ� ��ͣ��ѯ
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 PausePoll();

    /*�������� ResumePoll
    ��    �ܣ� ������ѯ
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 ResumePoll();

    /*�������� SendMessage
    ��    �ܣ� ������ն˷��Ͷ���Ϣ
    ��    ���� vector<CString> &vctMt �����ն�
               string strMsg ��Ϣ����
               BOOL32 bSelectAll ȫѡ
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 SendMessage(vector<CString> &vctMt, CString strMsg, BOOL32 bSelectAll = FALSE);

    /*�������� AcceptMt
    ��    �ܣ� ��Ӧ�ն� �����������ն����뷢�ԡ���ϯ���廰ʱ�����Ի����ȷ��
    ��    ���� CString strMtName �ն�����
               BOOL32 bAccept  TRUE����, FALSE�ܾ�
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 AcceptMt(CString strMtName, BOOL32 bAccept=TRUE);
    
    /*�������� RemoteDummy
    ��    �ܣ� ��ϯԶ������
    ��    ���� CString strMt
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 RemoteDummy(CString strMt);

    /*�������� RemoteSilent
    ��    �ܣ� ��ϯԶ�˾���
    ��    ���� CString strMt
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 RemoteSilent(CString strMt);


    //************�ն�����************************************************// 

    /*�������� UpdateCfgH323
    ��    �ܣ� H323����
    ��    ���� const TH323Cfg &tCfg(ȫ��)
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 UpdateCfgH323(const TH323Cfg &tCfg);

	/*�������� UpdateAVPrior
    ��    �ܣ� ��������Ƶ��ѡЭ��
    ��    ���� const TAVPriorStrategy &tCfg(ȫ��)
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 UpdateAVPrior(const TAVPriorStrategy &tCfg);
    /*�������� UpdateCfgOSD
    ��    �ܣ� ̨������
    ��    ���� const TOsdCfg &tCfg(ȫ��)
    �� �� ֵ�� BOOL32 
    ˵    ���� */	
	BOOL32 UpdateCfgOSD(const TOsdCfg &tCfg);

   /*�������� ChangeSign
    ��    �ܣ� ����̨��
    ��    ���� CString strBMPPath
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 ChangeSign(CString strBMPPath);

    /*�������� UpdateCfgNet
    ��    �ܣ� ��̫������
    ��    ���� const TEthnetInfo &tCfg(ȫ��)
				u8  byIndex    ������(һ���ն�Ҳֻ��һ������)
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 UpdateCfgNet(const TEthnetInfo &tCfg, u8 byIndex = 0);

	/*�������� UpdateCfgTrap
    ��    �ܣ� SNMP����
    ��    ���� const TSNMPCfg &tCfg(ȫ��)
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 UpdateCfgTrap(const TSNMPCfg &tCfg);

    /*�������� UpdateCfgUser
    ��    �ܣ� �û�����
    ��    ���� const TUserCfg &rCfg(�����Ƿ�����Զҡ������ȫ��)
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 UpdateCfgUser(const TUserCfg &tCfg);

	/*�������� UpdateCfgPPPoE
    ��    �ܣ� PPPoE����
    ��    ���� const TPPPOECfg &tCfg(ȫ��)
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 UpdateCfgPPPoE(const TPPPOECfg &tCfg);

	/*�������� updateCfgDHCP
    ��    �ܣ� PPPoE����
    ��    ���� const BOOL32 bUse
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 UpdateCfgDHCP(const BOOL32 bUse);

	/*�������� UpdateCfgFireWall
    ��    �ܣ� ����ǽ����
    ��    ���� const TEmbedFwNatProxy& tcfg(ȫ��)
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 UpdateCfgFireWall(const TEmbedFwNatProxy& tcfg);
	
	/*�������� UpdateCfgNapMap
    ��    �ܣ� ��̬ӳ��
    ��    ���� const TNATMapAddr& tcfg(ȫ��)
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 UpdateCfgNapMap(const TNATMapAddr& tcfg);
 
    /*�������� UpdateCfgVEnc
    ��    �ܣ� ��Ƶ��������
    ��    ���� const TVideoParam &rCfg(����H264��ѡ�����ȫ��)
				const EmVideoStandard emType  ��Ƶ��ʽ
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 UpdateCfgVEnc(const TVideoParam &tCfg, const EmVideoStandard emType);
    
    /*�������� Updatecfg264VEnc
    ��    �ܣ� ����264����
    ��    ���� const _TVENCPARAM &rCfg ����ֻ��Ҫ��д
    	        u16 wH264IKeyRate;		//h264�Ĺؼ�֡���
	            u8  byH264QualMaxValue;	//h264�����������
	            u8  byH264QualMinValue;	//h264��С��������
                ������
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 Updatecfg264VEnc(const TVideoParam &tCfg);
	/*�������� UpdateCfgQos
    ��    �ܣ� Qos����
    ��    ���� const TIPQoS &rCfg
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 UpdateCfgQos(const TIPQoS &tCfg);

 	/*�������� UpdateCfgAEnc
    ��    �ܣ� ��Ƶ��������
    ��    ���� const u8 &byInputVol			��������
			   const u8 &byOutPutVol		�������
    �� �� ֵ�� BOOL �Ƿ�ɹ�
    ˵    ���� */
	BOOL32 UpdateCfgAEnc(const u8 &byInputVol);
	BOOL32 UpdateCfgADec(const u8 &byOutPutVol);
   /*�������� UpdateCfgAEC
    ��    �ܣ� AEC������������
    ��    ���� BOOL32 bAEC		True ����			FALSE		�ر�
			   BOOL32 bAGC		True ����			FALSE		�ر�
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 UpdateCfgAEC(BOOL32 bAEC, BOOL32 bAGC);
	/*�������� UpdateCfgSendRt
    ��    �ܣ� �����ش�����
    ��    ���� const TLostPackResend &rCfg
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 UpdateLostPackReSend(const TLostPackResend &tCfg);

    /*�������� UpdateCfgPanel
    ��    �ܣ� ������ý������
    ��    ���� const TStreamMedia &tCfg(ȫ��)
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 UpdateCfgPanel(const TStreamMedia &tCfg);

    /*�������� UpdateCfgMatrix
    ��    �ܣ� ��������
    ��    ���� const _TDEVCFG
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 UpdateCfgMatrix(EmSerialType emType, TIPTransAddr &tIPAddr);

    /*�������� UpdateCfgCamera
    ��    �ܣ� ����ͷ����
    ��    ���� INT nIndex  ����ͷ��� 0 ~5
               const TCameraCfg &tCfg(ȫ��)
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 UpdateCfgCamera(s32 nIndex, const TCameraCfg &tCfg);

    /*�������� UpdateCfgTVOut
    ��    �ܣ� ��������ӿ�
    ��    ���� const TVideoSource &tCfg(ȫ��)
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 UpdateCfgVSource(const TVideoSource &tCfg); 

    /*�������� UpdateCfgSerialPort
    ��    �ܣ� ��������
    ��    ���� const TSerialCfg &tCfg(ȫ��)
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 UpdateCfgSerialPort(const EmSerialType &emType, const TSerialCfg &tCfg);
    
    /*�������� UpdateCfgImage
    ��    �ܣ� ͼ������
    ��    ���� const TImageAdjustParam & tCfg(ȫ��)
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 UpdateCfgImage(const TImageAdjustParam & tCfg,BOOL32 bReset = FALSE);

    /*�������� UpdaeteCfgDual
    ��    �ܣ� ����˫������
    ��    ���� const _TVENCPARAM &tCfg ����ֻ��
               "ͼ�������С��������"��"���ؼ�֡���"�� ��Ƶ�ɼ�֡�ʣ���������Ч
    �� �� ֵ�� 
    ˵    ���� �ṹû�ж���*/
//    BOOL32 UpdateCfgDual(const TVideoParam &tCfg);

    /*�������� UpdaeteCfgVGADual
    ��    �ܣ� ����VGA˫������
    ��    ���� const  TVideoParam(����H264����������Ч��) ����ֻ��
				֡��
				֡�ʵ�λ
               "���ؼ�֡���"
			   "ͼ�������С��������"�� 
               "���뷽ʽ"			emQualityFirst			0		// ��������
                                    emSpeedFirst			1		// �ٶ�����
               "֡�ʵ�λ(emFrameSecond:֡/ÿ�� emSecondFrame:��/ÿ֡)"
               ��������Ч
    �� �� ֵ�� 
    ˵    ���� */
    BOOL32 UpdateCfgVGADual(const TVideoParam &tCfg, const EmVideoStandard &emType);

    /*�������� UpdateCfgCaption
    ��    �ܣ� ���º������
    ��    ���� u8 byIndex		���1 ���Ǻ��2
				const TBannerInfo &tCfg
               CString &strCaption  �������
    �� �� ֵ�� 
    ˵    ���� �ṹû�ж���*/
    BOOL32 UpdateCfgCaption(u8 byIndex, const TBannerInfo &tCfg, CString &strCaption);

    /*�������� SetDefaultCfg
    ��    �ܣ� �ָ�Ĭ��ֵ
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 SetDefaultCfg();
	    /*�������� AddRoute
    ��    �ܣ� ����һ��·������ 
    ��    ���� const tIpRouteParam& tIpRouteParam Ҫ���ӵ�·��������Ϣ(ȫ��)
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 AddRoute(const TRouteCfg& tIpRouteParam);

    /*�������� DeleteRoute
    ��    �ܣ� ɾ��һ��·������ 
    ��    ���� u8 byIndex Ҫɾ����·����������
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 DeleteRoute(u8 byIndex);
	/*�������� UpdateE1Chan
	��    �ܣ� ����һ��E1  ͨ��
    ��    ���� const TE1Config(ȫ��)
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 UpdateE1Chan(const TE1Config& tE1Cfg);
	/*�������� DeleteE1Chan
	��    �ܣ� ɾ����ǰE1 ͨ��
    ��    ���� const 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 DeleteE1Chan();
	
       /*************ϵͳ���ӿ�*****************/
	/*�������� SelfLoop
    ��    �ܣ� �Ի�
    ��    ���� BOOL bStart TRUE ��ʼ,FALSE ֹͣ
    �� �� ֵ�� BOOL32 �ɹ�����TRUE��ʧ�ܷ���FALSE
    ˵    ���� */
	BOOL32 SelfLoop(BOOL bStart);

	/*�������� VolumnPowerTest
    ��    �ܣ� ��������
    ��    ���� BOOL bStart TRUE ��ʼ,FALSE ֹͣ
    �� �� ֵ�� BOOL32 �ɹ�����TRUE��ʧ�ܷ���FALSE
    ˵    ���� */
	BOOL32 VolumePowerTest(BOOL bStart);

	/*�������� ImageTest
    ��    �ܣ� ͼ�����
    ��    ���� BOOL bStart TRUE ��ʼ,FALSE ֹͣ
	           INT nType ��������
    �� �� ֵ�� BOOL32 �ɹ�����TRUE��ʧ�ܷ���FALSE
    ˵    ���� */
	BOOL32 ImageTest(BOOL bStart, INT nType);



	/*************�豸���ƽӿ�*****************/

	/*�������� RemoteCtrlClick
    ��    �ܣ� ң��������
    ��    ���� CString strBtnName��ť����
    �� �� ֵ�� BOOL32 �ɹ�����TRUE��ʧ�ܷ���FALSE
    ˵    ���� */
	BOOL32 RemoteCtrlClick(CString strBtnName);

	/*�������� SelectCamera
    ��    �ܣ� ѡ������ͷ
    ��    ���� INT nCamera ����ͷ���� 0 ΪԶ��
    �� �� ֵ�� BOOL32 �ɹ�����TRUE��ʧ�ܷ���FALSE
    ˵    ���� */
	BOOL32 SelectCamera(INT nCamera);

    /*�������� UpdateCamPreSet
    ��    �ܣ� ��������ͷԤ��
    ��    ���� BOOL bSave TRUE���� FALSE ����
	           INT nPosition Ԥ��λ
    �� �� ֵ�� BOOL32 �ɹ�����TRUE��ʧ�ܷ���FALSE
    ˵    ���� */
	BOOL32 UpdateCamPreSet(BOOL bSave, INT nPosition , BOOL32 bRemoteControl = FALSE);

    /*�������� SetMatrix
    ��    �ܣ� ���þ������ã����ߣ�
    ��    ���� _TMATRIXINFO tMatrixInfo ֻ��Ҫ��д
          	             u8  byPortNum;	//�˿ڸ���
                         u8  abyConfig[MATRIX_MAX_PORT];//�������ù�ϵ(����Ϊ����˿�)
               BYTE byType=1  �������� Ĭ��Ϊ��Ƶ����Ŀǰֻ֧����Ƶ�������
    �� �� ֵ�� BOOL32 
    ˵    ���� */
//    BOOL32 SetMatrix(_TMATRIXINFO tMatrixInfo, BYTE byType=1);


	/********************ϵͳ����****************************************************/

	/*�������� ModUser
    ��    �ܣ� �޸��û�
    ��    ���� 
    �� �� ֵ�� BOOL32 �ɹ�����TRUE��ʧ�ܷ���FALSE
    ˵    ���� */
	BOOL32 ModUser(const CUserFullInfo &user);

	/*�������� AddUser
    ��    �ܣ� �����û�
    ��    ���� 
    �� �� ֵ�� BOOL32 �ɹ�����TRUE��ʧ�ܷ���FALSE
    ˵    ���� */
	BOOL32 AddUser(const CUserFullInfo &user);

	/*�������� DelUser
    ��    �ܣ� ɾ���û�
    ��    ���� 
    �� �� ֵ�� BOOL32 �ɹ�����TRUE��ʧ�ܷ���FALSE
    ˵    ���� */
	BOOL32 DelUser(const CUserFullInfo &user);

    /*�������� AddEntry
    ��    �ܣ� ������Ŀ
    ��    ���� TADDRENTRYINFO &tEntryInfo  ��ַ��Ŀ��Ϣ
			   (������Ƿ�320�ն˺�320�ն˱��������д���)
    �� �� ֵ�� BOOL32 �ɹ�����TRUE��ʧ�ܷ���FALSE
    ˵    ���� */
	BOOL32 AddEntry(const TADDRENTRYINFO &tEntryInfo);

    /*�������� ModifyEntry
    ��    �ܣ� �޸���Ŀ
    ��    ���� CString &strOldEntryName ԭ��������
               CString &strEntryName    �޸ĺ������
               DWORD dwIP
               CString &strAlias
               CString &strE164
               u16 wBitRate
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 ModifyEntry(const TADDRENTRYINFO& tOldInfo, const TADDRENTRYINFO& tNewInfo);

    /*�������� DeleteEntry
    ��    �ܣ� ɾ����Ŀ
    ��    ���� CString &strEntryName ��Ŀ����
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 DeleteEntry(const CString &strEntryName);
    BOOL32 DeleteEntry(const TADDRENTRYINFO &tEntyInfo);

    /*�������� AddGroup
    ��    �ܣ� ������
    ��    ���� CString &strGroupName  ����
               DWORD dwIP IP
               u16 wBitRate
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 AddGroup(const CString &strGroupName, DWORD dwIP, u16 wBitRate);
    /*�������� ModifyGroup
    ��    �ܣ� �޸���
    ��    ���� CString &strOldGroupName ԭ��������
               CString &strGroupName    �޸ĺ������
               DWORD dwIP
               u16 wBitRate
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 ModifyGroup(const CString &strOldGroupName, const CString &strGroupName, DWORD dwIP, u16 wBitRate);

    /*�������� DeleteGroup
    ��    �ܣ� ɾ����
    ��    ���� CString strGroupName
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 DeleteGroup(const CString &strGroupName);

    /*�������� AddEntryToGroup
    ��    �ܣ� �����Ŀ����
    ��    ���� CString &strGroupName
               vector<CString> vctAddrEntry
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 AddEntryToGroup(const CString &strGroupName,vector<TADDRENTRYINFO> &vtEntryInfo);

    /*�������� FindEntry
    ��    �ܣ� ������Ŀ
    ��    ���� CString &strGroupName(����/MCU��ַ)
               CString &strEntryName(����/����/IP��ַ/����)
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 FindEntry(const CString &strGroupName,const CString &strEntryName);

    /*�������� DelEntryFromGroup
    ��    �ܣ� ����ɾ����Ŀ
    ��    ���� CString &strGroupName 
               vector<CString> vctAddrEntry ��Ŀ��
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 DelEntryFromGroup(const CString &strGroupName, vector<TADDRENTRYINFO> &vtEntryInfo);

    /*�������� ClearAddrBook
    ��    �ܣ� �����Ŀ����
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 ClearEntry();
    BOOL32 ClearGroup();

    /*�������� ClearUser
    ��    �ܣ� ������е��û� 
    ��    ���� 
    �� �� ֵ�� BOOL32 
    ˵    ���� */
    BOOL32 ClearUser();

    /*�������� DynSwitchVmpStyle
    ��    �ܣ� ��̬�л�����ϳɷ�� 
    ��    ���� u8 nType ���л����Ļ���ϳɷ��
    �� �� ֵ�� BOOL32 
    ˵    ���� */
	BOOL32 DynSwitchVmpStyle(u8 nType);

   
public:	
    CGuiUnit			m_cGuiUnit;   //��������ӿ������
    HWND                m_hWndIE;     //IE�����������ھ��
    BOOL32              m_bResult;    //����������
protected:
	//�ն˿���̨����ؼ����
	bool bInitHandle;       //�Ƿ��Ѿ���ʼ�����
    HWND m_hDgForm;			//��Dialog
    //��ͷ��ť
	HWND m_hBtSnapCap;		    //����ͼƬ
    HWND m_hDualVideo;          //˫��
	HWND m_hBtAddrBook;		    //��ַ��
    HWND m_hSleepMt;            //����
    HWND m_hResetMt;            //��λ
    HWND m_hAbout;              //����
	HWND m_hUpLoad;				//�ϴ�
	//������ť
    HWND m_hbtnManageSystem;    //ϵͳ���� 
    HWND m_hbtnManageDevice;    //�豸����
    HWND m_hbtnManageDetect;    //ϵͳ���
    HWND m_hbtnManageConfig;    //�豸����
    HWND m_hbtnManageConf;      //�������
    HWND m_hstSheetTitle;       //ҳ����ʾ
    //����Ϣ
    HWND m_heditShortMsg;       //������Ϣ�༭��           
    HWND m_heditMsgBoard;       //����Ϣ��ʾ��          
    HWND m_heditMsgInfo;        //ϵͳ��Ϣ
    HWND m_hlbMsgMt;            //���Ͷ���Ϣ�Ŀ�ѡ�ն��б�
    HWND m_hbtnPresetMsg;       //Ԥ��     
    HWND m_hbtnLoadMsg;         //����     
    HWND m_hbtnSendSms;         //���� 

    //�����еİ�ť    
    HWND m_hbtnPipSwitch;      //�����л�
    HWND m_hbtnPipMove;        //�����ƶ�
    HWND m_hbtnVoiceSpark;     //���Լ���
    HWND m_hbtnVMP;            //���渴��
    HWND m_hbtnConfDiscuss;    //��������    
    HWND m_hbtnP2PCall;        //����      
    HWND m_hbtnCreateConf;     //����
    HWND m_hlsPlatform;        //��ϯ̨     
    HWND m_hlsAudience;        //����̨     
    HWND m_hstConfName;        //��������
    //���
    HWND m_hbtnSnapshotRemote; //
    HWND m_hbtnSnapshotLocal;  //
    HWND m_hbtnFullRemote;     //     
    HWND m_hbtnFullLocal;      //     
    HWND m_hbtnMute;           //     
    HWND m_hbtnDumb;           //    
    HWND m_hbtnStartRemote;    //     
    HWND m_hbtnStartLocal;     // 
    HWND m_hstRemoteName;      //     
    HWND m_hstLocalMtName;     //
    HWND m_hstLocalMonitor;    //���ؼ��ͼ�񴰿�
    HWND m_hstRemoteMonitor;   //Զ�˼��ͼ�񴰿�

    CString m_strChairman;     //��ϯ
    CString m_strSpeaker;	   //������
    CString m_strMe;           //�����ն˱���
};

#endif // !defined(AFX_UIOPINTERFACE_H__57F5B3B1_71A8_4327_8ADC_7BB80C75C02F__INCLUDED_)
