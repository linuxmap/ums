/*=============================================================================
ģ   ��   ��: USB-KEY����
��   ��   ��: UsbKey.h
�� ��  �� ��: UsbKey.cpp
�ļ�ʵ�ֹ���: USB��������
��        ��: ���
��        ��: V4.0  Copyright(C) 2006-2006 Kedacom, All rights reserved.
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���      �޸�����
2006/10/11  1.0     ���        ����
=============================================================================*/

// UsbKey.h: interface for the CUsbKey class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USBKEY_H__07466CA1_8127_40AA_A02F_7C86D612ADE0__INCLUDED_)
#define AFX_USBKEY_H__07466CA1_8127_40AA_A02F_7C86D612ADE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "kdvtype.h"
#include <wtypes.h>
#include "hkapi.h"


#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

//��Ȩģ����Ϣ
enum EMUsbRight
{
    enumUsbRightMCS     = 1,    //MCS
    enumUsbRightPCMT    = 2,    //PCMT
    enumUsbRightNMS     = 3,    //NMS
    enumUsbRightVOS     = 4     //Recorder��VOD
};

//ģ�����/�γ��Ļص�����
typedef u32 (__stdcall* TUsbVerifyCallBack)(IN void *pCBData);

//USBKEY �豸��Ϣ����
#define VERSION_40_R3_1                 (LPCSTR)"kdv40.30.01.01.20061013"

#define CURRENT_VERSION                 VERSION_40_R3_1


#define MAXLEN_USBKEY_READER_NAME       (s32)128                //USBKEY������������
#define MAXLEN_USBKEY_READER_NUM        (s32)12                 //USBKEY������������
//����USBKEY�豸����󳤶�, ��'\0'
#define MAXLEN_USBKEY_NAME              MAXLEN_USBKEY_READER_NAME * MAXLEN_USBKEY_READER_NUM
#define DEFAULT_USBKEY_SO_PIN           (s8*)"1111"             //Ĭ�Ϲ���Ա����
#define DEFAULT_USBKEY_USER_PIN         (s8*)"1111"             //Ĭ���û�����
#define DEFAULT_USBKEY_TAG_PREFIX       (LPCSTR)"kdv40.30.01.01.20061013"//USBKEY�豸��ǩ��ǰ׺
#define MAXLEN_USBKEY_DEVICE_TAG        (u32)128                //���USBKEY�豸��ǩ������
#define DEFAULT_USBKEY_DIRID            (u32)0xDF02             //USBKEY�豸ȱʡ����Ȩ��ϢĿ¼ID
//#define USBKEY_VERSION_DIRID            (u32)0xDF21
#define USBKEY_VERSION_FILEID           (u32)0xEF21
//#define USBKEY_MCS_DIRID                (u32)0xDF22
#define USBKEY_MCS_FILEID               (u32)0xEF22
//#define USBKEY_PCMT_DIRID               (u32)0xDF23
#define USBKEY_PCMT_FILEID              (u32)0xEF23
//#define USBKEY_NMS_DIRID                (u32)0xDF24
#define USBKEY_NMS_FILEID               (u32)0xEF24
//#define USBKEY_VOS_DIRID                (u32)0xDF25
#define USBKEY_VOS_FILEID               (u32)0xEF25
#define DEFAULT_USBKEY_FILESIZE         (u32)512                //USBKEY�豸ȱʡ����Ȩ��Ϣ�ļ��ռ�ߴ�(���ֽڼ���)
#define DEFAULT_USBKEY_AES_KEY          (s8*)"kedacom.shanghai" //USBKEY�豸ȱʡ����Ȩ��ϢAES��Կ
#define DEFAULT_USBKEY_AES_INITKEY      (s8*)"2003091919190900" //USBKEY�豸ȱʡ����Ȩ��ϢAES��ʼKEY
#define DEFAULT_USBKEY_AES_MODE         MODE_CBC                //USBKEY�豸ȱʡ����Ȩ��ϢAESģʽ


//������Ϣ
typedef struct tagUsbSaveInfo
{
public:
    tagUsbSaveInfo()
    {
        memset( this, 0, sizeof (tagUsbSaveInfo) );
    }

public:
    EMUsbRight      m_emUsbRight;       //����ģ��
} TUsbSaveInfo;

typedef struct tagUsbMcsSaveInfo : TUsbSaveInfo
{
public:
    tagUsbMcsSaveInfo() : m_bEnable(FALSE)
    {
        m_emUsbRight = enumUsbRightMCS;
    }

public:
    BOOL32  m_bEnable;      //�Ƿ�ʹ��
} TUsbMcsSaveInfo;

typedef struct tagUsbPcmtSaveInfo : TUsbSaveInfo
{
public:
    tagUsbPcmtSaveInfo() : m_bEnable(FALSE)
    {
        m_emUsbRight = enumUsbRightPCMT;
    }

public:
    BOOL32  m_bEnable;      //�Ƿ�ʹ��
} TUsbPcmtSaveInfo;

typedef struct tagUsbNmsSaveInfo : TUsbSaveInfo
{
public:
    tagUsbNmsSaveInfo() : m_bEnable(FALSE)
    {
        m_emUsbRight = enumUsbRightNMS;
    }

public:
    BOOL32  m_bEnable;      //�Ƿ�ʹ��
} TUsbNmsSaveInfo;

typedef struct tagUsbVosSaveInfo : TUsbSaveInfo
{
public:
    tagUsbVosSaveInfo() : m_bEnable(FALSE)
    {
        m_emUsbRight = enumUsbRightVOS;
    }

public:
    BOOL32  m_bEnable;      //�Ƿ�ʹ��
} TUsbVosSaveInfo;



//����, �ⲿ��Ҫ����
class CUsbKey  
{
public:
	CUsbKey();
	virtual ~CUsbKey();

protected:
    /*=============================================================================
    �� �� ��:EnumReaders
    ��    ��:ö�����ж�������
    ��    ��:OUT s8 aaszAllReaders[][]                  [out]   ���ж�������, ��0x00�ָ�
             OUT s32 &nReaderNum                        [out]   ����������
    ע    ��:��������GetErrorDescription����
    �� �� ֵ:��ȡ�ɹ�: 0; ��ȡʧ��: ������
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/10/11  1.0     ���    ����
    =============================================================================*/
    u32 EnumReaders(OUT s8 aaszAllReaders[MAXLEN_USBKEY_READER_NUM][MAXLEN_USBKEY_READER_NAME],
                    OUT s32 &nReaderNum);

    /*=============================================================================
    �� �� ��:SaveData
    ��    ��:��������
    ��    ��:IN HKHANDLE hCard                      [in]    ���������
             IN EMUsbRight emRight                  [in]    ģ��
             IN const u8 *pbyBuf                    [in]    ��������
             IN s32 nBufLen                         [in]    ���ݳ���
    ע    ��:��������GetErrorDescription����; ����ǰ��򿪶�����, ����ռ�豸
             ���ú�, ������ռ, ���ر��豸
    �� �� ֵ:����ɹ�: 0; ����ʧ��: ������
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/10/12  1.0     ���    ����
    =============================================================================*/
    u32 SaveData(IN HKHANDLE hCard, IN EMUsbRight emRight,
                 IN const u8 *pbyBuf, IN s32 nBufLen);

    /*=============================================================================
    �� �� ��:ReadData
    ��    ��:��ȡ����
    ��    ��:IN HKHANDLE hCard                      [in]    ���������
             IN EMUsbRight emRight                  [in]    ģ��
             OUT const u8 *pbyBuf                   [out]   ����
             IN OUT s32 nBufLen                     [in]    ������󳤶�
    ע    ��:��������GetErrorDescription����; ����ǰ��򿪶�����, ����ռ�豸
             ���ú�, ������ռ, ���ر��豸
    �� �� ֵ:��ȡ�ɹ�: 0; ��ȡʧ��: ������
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/10/12  1.0     ���    ����
    =============================================================================*/
    u32 ReadData(IN HKHANDLE hCard, IN EMUsbRight emRight,
                 OUT u8 *pbyBuf, IN OUT s32 nBufLen);

    /*=============================================================================
    �� �� ��:SaveVersion
    ��    ��:����汾��
    ��    ��:IN HKHANDLE hCard                      [in]    ���������
    ע    ��:��������GetErrorDescription����; ����ǰ��򿪶�����, ����ռ�豸
             ���ú�, ������ռ, ���ر��豸
    �� �� ֵ:����ɹ�: 0; ����ʧ��: ������
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/10/12  1.0     ���    ����
    =============================================================================*/
    u32 SaveVersion(IN HKHANDLE hCard);

    /*=============================================================================
    �� �� ��:ReadVersion
    ��    ��:��ȡ�汾��
    ��    ��:IN HKHANDLE hCard                      [in]    ���������
             OUT LPSTR lptrVersion                  [out]   �汾��
    ע    ��:��������GetErrorDescription����; ����ǰ��򿪶�����, ����ռ�豸
             ���ú�, ������ռ, ���ر��豸
    �� �� ֵ:��ȡ�ɹ�: 0; ��ȡʧ��: ������
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/10/12  1.0     ���    ����
    =============================================================================*/
    u32 ReadVersion(IN HKHANDLE hCard, OUT LPSTR lptrVersion);

public:
    /*=============================================================================
    �� �� ��:GetWorkingReaders
    ��    ��:��ȡ��ǰ���п��ö�����
    ��    ��:OUT s8 aaszReaders[][]                         [out]   ��ǰ���п��ö�������
             OUT s32 &nReaderNum                            [out]   ���ö���������
    ע    ��:��������GetErrorDescription����
    �� �� ֵ:��ȡ�ɹ�: 0; ��ȡʧ��: ������
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/10/11  1.0     ���    ����
    =============================================================================*/
    u32 GetWorkingReaders(OUT s8 aaszReaders[MAXLEN_USBKEY_READER_NUM][MAXLEN_USBKEY_READER_NAME],
                          OUT s32 &nReaderNum);

    /*=============================================================================
    �� �� ��:GetErrorDescription
    ��    ��:��ȡ��������
    ��    ��:IN TUsbVerifyCallBack pFuncCallBack    [in]    �ص�����
             IN u8 byLanguage                       [in]    ��������(0: ����; 1: Ӣ��)
    ע    ��:����ֻ������
    �� �� ֵ:��������
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/10/11  1.0     ���    ����
    =============================================================================*/
    static LPCTSTR GetErrorDescription(IN u32 dwErrCode, IN u8 byLanguage = 0);
};

#endif // !defined(AFX_USBKEY_H__07466CA1_8127_40AA_A02F_7C86D612ADE0__INCLUDED_)
