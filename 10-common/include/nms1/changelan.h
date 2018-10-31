/*****************************************************************************
  ģ����      : changelan.lib
  �ļ���      : changelan.h
  ����ļ�    : changelandef.h
  �ļ�ʵ�ֹ���: ���봰�����֡���ָ������
  ����        : ������
  �汾        : V1.0  Copyright(C) 1997-2005 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���                 �޸�����
2005/09/09  1.0         ������                 ����
******************************************************************************/
#ifndef _CHANGELAN_050909_H_
#define _CHANGELAN_050909_H_


class CTranslate;
class CChangeLan
{
public:
    CChangeLan();
    ~CChangeLan();
    /*��������    Create
    ��    �ܣ� 
    ��    ���� LPCTSTR lpszFileName:�����ı���Ϣ���ļ���
               u32 nMaxNode = 1000:���е��ı����������ڷ����ڴ档
    �� �� ֵ��  
    ˵    ���� */
    u16     Create(LPCTSTR lpszFileName, u32 nMaxNode = 1000);

    u16     Destroy();

    /*��������    SetCurLanguage
    ��    �ܣ� ���벢���õ�ǰ����������
    ��    ���� LPCTSTR lpszLangName���µ��������͡�
               HWND hTopWnd = NULL�������µ����ԣ������趨���ڼ����Ӵ�������
    �� �� ֵ��  
    ˵    ���� */
    u16     SetCurLanguage(LPCTSTR lpszLangName, HWND hTopWnd = NULL);


    /*�������� TranslateText
    ��    �ܣ� ����ָ�����ֵ�ָ����������
    ��    ���� LPCTSTR lpszOld������������ֵ���������
               LPCTSTR lpszNew������Ŀ����������
               LPCTSTR lpszText�������������
    �� �� ֵ�� ���������֣�ʧ�ܷ���NULL
    ˵    ���� */
    LPCTSTR TranslateText(LPCTSTR lpszOld, LPCTSTR lpszNew, LPCTSTR lpszText);
    /*�������� TranslateText
    ��    �ܣ� ����ָ�����ֵ���ǰ��������
    ��    ���� LPCTSTR lpszLangType������������ֵ���������
               LPCTSTR lpszText�������������
    �� �� ֵ�� ���������֣�ʧ�ܷ���NULL
    ˵    ���� */
	LPCTSTR TranslateText(LPCTSTR lpszLangType, LPCTSTR lpszText);

    /*�������� TranslateFromENG
    ��    �ܣ� ����ָ��Ӣ�����ֵ���ǰ��������
    ��    ���� LPCTSTR lpszText�������������
    �� �� ֵ�� ���������֣�ʧ�ܷ���NULL
    ˵    ���� */
    LPCTSTR TranslateFromENG(LPCTSTR lpszText);
    /*�������� TranslateFromCHN
    ��    �ܣ� ����ָ���������ֵ���ǰ��������
    ��    ���� LPCTSTR lpszText�������������
    �� �� ֵ�� ���������֣�ʧ�ܷ���NULL
    ˵    ���� */
    LPCTSTR TranslateFromCHN(LPCTSTR lpszText);

    /*�������� TurnWindowText
    ��    �ܣ� ����ָ�����ڼ����Ӵ������ֵ�ָ�����ԣ�
    ��    ���� LPCTSTR lpszOld������ǰ������ʹ�õ����ԡ�
               LPCTSTR lpszNew������󣬴���ʹ�õ����ԡ�
               HWND hTopWnd��   ���ھ��
    �� �� ֵ�� ������
    ˵    ���� */
    u16 TurnWindowText(LPCTSTR lpszOld, LPCTSTR lpszNew, HWND hTopWnd);
    /*�������� TurnWindowText
    ��    �ܣ� ���봰�ڼ����Ӵ������ֵ���ǰ���ԣ�
    ��    ���� LPCTSTR lpszOld�����ڵ�ǰʹ�õ�����
               HWND hTopWnd��   ���ھ��
    �� �� ֵ�� ������
    ˵    ���� */
	u16 TurnWindowText(LPCTSTR lpszOld, HWND hTopWnd);

    /*�������� TurnMenuText
    ��    �ܣ� ����˵��е����֡�
    ��    ���� LPCTSTR lpszOld������ǰ���˵�ʹ�õ����ԡ�
               LPCTSTR lpszNew������󣬲˵�ʹ�õ����ԡ�
               HMENU hMenu��    �˵������
    �� �� ֵ�������� 
    ˵    ���� */
    u16 TurnMenuText(LPCTSTR lpszOld, LPCTSTR lpszNew, HMENU hMenu);

    /*�������� TurnMenuText
    ��    �ܣ� ����˵��е����ֵ���ǰ������
    ��    ���� LPCTSTR lpszOld������ǰ���˵�ʹ�õ����ԡ�
               HMENU hMenu
    �� �� ֵ�� ������
    ˵    ���� */
    u16 TurnMenuText(LPCTSTR lpszOld, HMENU hMenu);
    
    /*�������� SetNotifyMessage
    ��    �ܣ� 
    ��    ���� u32 dwMesssageID��֪ͨ��ϢIDĬ��ΪWM_USER+11
               u8 bySendMode��SENDMSG_MODE_ALLȫ�����ڣ�
                              SENDMSG_MODE_IGNORE���Դ��ڣ�Ĭ�ϣ���
    �� �� ֵ�� 
    ˵    ���� */
    u16 SetNotifyMessage(u32 dwMesssageID, u8 bySendMode);

    /*�������� GetCurrentLan
    ��    �ܣ� 
    ��    ���� 
    �� �� ֵ����ǰ���� 
    ˵    ���� */
    LPCTSTR GetCurrentLan() const;

	static u16 SetIgnoreWnd(HWND hWnd, BOOL32 bIgnore = TRUE);
protected:
    CTranslate*     m_pTran;
};
#endif