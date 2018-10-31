/*=======================================================================
ģ����      : �ļ�����������
�ļ���      : filesrvclientstruct.h
����ļ�    : ��
�ļ�ʵ�ֹ���: �������ṹ����(��Ҫ����ͻ��˵Ľṹ)
����        : ���
�汾        : V1.0  Copyright(C) 2006-2007 KDC, All rights reserved.
-------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2006/12/28  1.0     ���    ����
=======================================================================*/

#ifndef _FILESRVCLIENTSTRUCT_H
#define _FILESRVCLIENTSTRUCT_H

#ifdef WIN32
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#endif//WIN32

#include "filesrvstruct.h"
#include "ummessagestruct.h"

#ifdef WIN32
    #pragma pack( push )
    #pragma pack( 1 )
    #define window( x )	x
#else
    #include <netinet/in.h>
    #define window( x )
#endif//WIN32

/*------------------------------------------------------------------------------
  ��������ͻ��˽����ṹ
------------------------------------------------------------------------------*/

//����汾�Žṹ
typedef struct tagFCSoftwareVer//len: 16
{
public:
    tagFCSoftwareVer() : m_wMainVer(0), m_wSubVer(0), m_wInterfaceVer(0),
                           m_wModifyVer(0), m_dwDate(0), m_dwReserved1(0)
    {}

    tagFCSoftwareVer(u16 wMainVer, u16 wSubVer, u16 wIntVer, u16 wModVer,
                     u32 dwDate) : m_dwReserved1(0)
    {
        m_wMainVer      = htons( wMainVer );
        m_wSubVer       = htons( wSubVer );
        m_wInterfaceVer = htons( wIntVer );
        m_wModifyVer    = htons( wModVer );
        m_dwDate        = htonl( dwDate );
    }

    tagFCSoftwareVer(LPCSTR lptrVer) : m_dwReserved1(0)
    { FromString( lptrVer ); }

    //�ÿ�
    inline void SetNull(void) { memset( this, 0, sizeof (tagFCSoftwareVer) ); }

    //�������汾��
    inline void SetMainVer(u16 wMainVer) { m_wMainVer = htons( wMainVer ); }

    //��ȡ���汾��
    inline u16 GetMainVer(void) const { return ntohs( m_wMainVer ); }

    //���ø��汾��
    inline void SetSubVer(u16 wSubVer) { m_wSubVer = htons( wSubVer ); }

    //��ȡ���汾��
    inline u16 GetSubVer(void) const { return ntohs( m_wSubVer ); }

    //���ýӿڰ汾��
    inline void SetInterfaceVer(u16 wInterfaceVer)
    { m_wInterfaceVer = htons( wInterfaceVer ); }

    //��ȡ�ӿڰ汾��
    inline u16 GetInterfaceVer(void) const { return ntohs( m_wInterfaceVer ); }

    //�����޸İ汾��
    inline void SetModifyVer(u16 wModifyVer)
    { m_wModifyVer = htons( wModifyVer ); }

    //��ȡ�޸İ汾��
    inline u16 GetModifyVer(void) const { return ntohs( m_wModifyVer ); }

    //��������
    inline void SetDate(u32 dwDate) { m_dwDate = htonl( dwDate ); }

    //��ȡ����
    inline u32 GetDate(void) const { return ntohl( m_dwDate ); }

    //�Ƚϰ汾
    inline BOOL32 operator<(const tagFCSoftwareVer &tVer)
    {
        return ( memcmp( this, &tVer, sizeof (tagFCSoftwareVer) ) < 0 );
    }
    inline BOOL32 operator>(const tagFCSoftwareVer &tVer)
    {
        return ( memcmp( this, &tVer, sizeof (tagFCSoftwareVer) ) > 0 );
    }
    inline BOOL32 operator==(const tagFCSoftwareVer &tVer)
    {
        return ( memcmp( this, &tVer, sizeof (tagFCSoftwareVer) ) == 0 );
    }

    //ת���ַ���
    inline void ToString(s8 szVer[MAX_FILESRV_SOFTVER_LEN]) const
    {
//         sprintf( szVer, "%.2d.%.2d.%.2d.%.2d.%.6d", ntohs( m_wMainVer ),
//                  ntohs( m_wSubVer ), ntohs( m_wInterfaceVer ),
//                  ntohs( m_wModifyVer ), ntohl( m_dwDate ) );
        sprintf( szVer, "%d.%d.%d.%d.%.6d", ntohs( m_wMainVer ),
                 ntohs( m_wSubVer ), ntohs( m_wInterfaceVer ),
                 ntohs( m_wModifyVer ), ntohl( m_dwDate ) );
        return;
    }

	inline int FindChar(LPCSTR lpStr, char chChar, int nStartPos)
	{
		int nPos = nStartPos;
		char chCurChar;
		int nLenth = strlen(lpStr);
		for (; nPos < nLenth; nPos++)
		{
			chCurChar = *(lpStr + nPos);
			if (chCurChar == chChar)
			{
				return nPos;
			}
		}
		return -1;

	}
    //���ַ�����ȡ
    inline BOOL32 FromString(LPCSTR lptrVer)
    {
//         if ( lptrVer == NULL || strlen(lptrVer) != 18 )
//         {
//             return FALSE;
//         }
//         m_wMainVer      = htons( atoi( lptrVer ) );
//         m_wSubVer       = htons( atoi( lptrVer + 3 ) );
//         m_wInterfaceVer = htons( atoi( lptrVer + 6 ) );
//         m_wModifyVer    = htons( atoi( lptrVer + 9 ) );
//         m_dwDate        = htonl( atoi( lptrVer + 12) );

		m_wMainVer = htons( atoi( lptrVer ) );

		int nPos = FindChar(lptrVer, '.', 0 );
		m_wSubVer = htons( atoi( lptrVer + nPos + 1 ) );

        nPos = FindChar(lptrVer, '.', nPos + 1 );
		m_wInterfaceVer = htons( atoi( lptrVer + nPos + 1 ) );

		nPos = FindChar(lptrVer, '.', nPos + 1 );
		m_wModifyVer = htons( atoi( lptrVer + nPos + 1 ) );

		nPos = FindChar(lptrVer, '.', nPos + 1 );
		m_dwDate = htonl( atoi( lptrVer + nPos + 1 ) );

     

        return TRUE;
    }

private:
    u16         m_wMainVer;//���汾�ţ�40.30.01.02.061111�����汾��Ϊ40
    u16         m_wSubVer;//���汾�ţ�40.30.01.02.061111�����汾��Ϊ30
    u16         m_wInterfaceVer;//�ӿڰ汾�ţ�40.30.01.02.061111���ӿڰ汾��Ϊ01
    u16         m_wModifyVer;//�޸İ汾�ţ�40.30.01.02.061111���޸İ汾��Ϊ02
    u32         m_dwDate;//���ڰ汾�ţ�40.30.01.02.061111�����ڰ汾��Ϊ061111
    u32         m_dwReserved1;//�����ֶ�
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif//WIN32
IFCSoftwareVer
;

typedef struct tagFCHardwareVer//len: 32
{
public:
    tagFCHardwareVer() { SetNull(); }

    //�ÿ�
    inline void SetNull(void)
    { memset( this, 0, sizeof (tagFCHardwareVer) ); }

    //����Ӳ���汾��
    inline void SetHardwareVer(u32 dwHardwareVer)
    {
        SetNull();
        *reinterpret_cast<u32*>(m_szHardwareVer) = htonl( dwHardwareVer );
    }

    //����Ӳ���汾��
//    BOOL32 AddHardwareVer(u8 byHardwareVer)
//    {
//        if ( m_szHardwareVer[sizeof (m_szHardwareVer) - 1] == 0 )
//        {
//            for ( s32 nIndex = 0; nIndex < sizeof (m_szHardwareVer); nIndex ++ )
//            {
//                if ( m_szHardwareVer[nIndex] == 0 )
//                {
//                    m_szHardwareVer[nIndex] = byHardwareVer + 1;
//                    break;
//                }
//                break;
//            }
//            return TRUE;
//        }
//        else
//        {
//            return FALSE;
//        }
//    }
//
//    //ָ��Ӳ���汾���Ƿ��ڷ�Χ֮��
//    BOOL32 IsHardwareVerValid(u8 byHardwareVer)
//    {
//        for ( s32 nIndex = 0; nIndex < sizeof (m_szHardwareVer) - 1; nIndex ++ )
//        {
//            if ( m_szHardwareVer[nIndex] == 0 )
//            {
//                return FALSE;
//            }
//            else if ( m_szHardwareVer[nIndex] == byHardwareVer + 1 )
//            {
//                return TRUE;
//            }
//        }
//        return FALSE;
//    }
//
//    //ָ��Ӳ���汾���Ƿ��ڷ�Χ֮��
//    BOOL32 IsHardwareVerValid(const s8 szHardVer[MAX_FILESRV_HARDVER_LEN])
//    {
//        s32 nIndex = 0;
//        s32 nIdx = 0;
//        for ( ; m_szHardwareVer[nIndex] != '\0'; nIndex ++ )
//        {
//            for ( ; szHardVer[nIdx] != '\0'; nIdx ++ )
//            {
//                if ( m_szHardwareVer[nIndex] == szHardVer[nIdx] )
//                {
//                    return FALSE;
//                }
//            }
//        }
//        return (nIndex > 0 && nIdx > 0 ) ? TRUE : FALSE;
//    }
//
//    //���
//    BOOL32 RemoveConflictVer(const s8 szHardVer[MAX_FILESRV_HARDVER_LEN])

    //����Ӳ���汾��
    inline void SetHardwareVer(LPSTR lptrHardwareVer)
    {
        SetNull();
        if ( lptrHardwareVer != NULL )
        {
            strncpy( m_szHardwareVer, lptrHardwareVer,
                     sizeof (m_szHardwareVer) - 1 );
        }
    }

    //��ȡӲ���汾��
  inline LPCSTR GetHardwareVer(void) const { return m_szHardwareVer; }

private:
    s8          m_szHardwareVer[MAX_FILESRV_HARDVER_LEN];
}
#ifndef WIN32
__attribute__ ( (packed) )
#endif//WIN32
IFCHardwareVer
;

class CFCSrvUserInfo : public CUserFullInfo//len: 257
{
public:
    CFCSrvUserInfo() : CUserFullInfo(), m_dwUserNo(0) {}

    ~CFCSrvUserInfo() {}

    //�����û����
    inline void SetUserNo(u32 dwUserNo) { m_dwUserNo = htonl( dwUserNo ); }

    //��ȡ�û����
    inline u32 GetUserNo(void) const { return ntohl( m_dwUserNo ); }

private:
    u32 m_dwUserNo;     //�û����
}
#ifndef WIN32
__attribute__ ( (packed) )
#endif//WIN32
;

//�ͻ��˵�¼�ṹ
typedef struct tagFCSrvLoginInfo//len: 64
{
public:
    tagFCSrvLoginInfo() { SetNull(); }

    //�ÿ�
    inline void SetNull(void) { memset( this, 0, sizeof (tagFCSrvLoginInfo) ); }

    //��ȡ�û���
    inline LPCSTR GetUserName(void) const { return m_szUserName; }

    //�����û������벻�ü���
    BOOL32 SetUser(LPCSTR lptrUser, LPCSTR lptrPwd)
    {
        SetNull();
        if ( lptrUser == NULL )
        {
            return FALSE;
        }
        strncpy( m_szUserName, lptrUser, sizeof (m_szUserName) - 1 );
        if ( lptrPwd != NULL )
        {
            CMD5Encrypt cMd5;
            s8 szPwd[32];
            cMd5.GetEncrypted( const_cast<LPSTR>(lptrPwd),
                               const_cast<LPSTR>(szPwd) );
            strncpy( m_szPassword, szPwd, sizeof (m_szPassword) - 1 );
        }
        return TRUE;
    }

    //��ȡ����(�Ѽ���)
    inline LPCSTR GetPassword(void) const { return m_szPassword; }

private:
    s8      m_szUserName[MAX_FILESRV_USERNAME_LEN];//�û���
    s8      m_szPassword[MAX_FILESRV_PASSWORD_LEN];//����MD5���ܵ�����
}
#ifndef WIN32
__attribute__ ( (packed) )
#endif//WIN32
IFCSrvLoginInfo
;

//�豸��ʶ
typedef struct tagFCSrvDev//len: 4
{
public:
    tagFCSrvDev() : m_byDevType(0), m_byDevModel(0), m_byDevOsType(0),
    	            m_byReserved1(0)
    {}

    tagFCSrvDev(u8 byDevType, u8 byDevModel, u8 byDevOsType)
        : m_byDevType(byDevType), m_byDevModel(byDevModel),
          m_byDevOsType(byDevOsType), m_byReserved1(0) {}

    tagFCSrvDev(s8 szType[MAX_FILESRV_DEVSTRING_LEN]) : m_byReserved1(0)
    { FromString( szType ); }

    //�ÿ�
    inline void SetNull(void) { memset( this, 0, sizeof (tagFCSrvDev) ); }

    //�����豸����
    inline void SetType(EMFileSrvDevType emDevType)
    { m_byDevType = static_cast<u8>(emDevType); }

    //��ȡ�豸����
    inline EMFileSrvDevType GetType(void) const
    { return static_cast<EMFileSrvDevType>(m_byDevType); }

    //�����豸�ͺ�
    inline void SetModel(u8 byDevModel) { m_byDevModel = byDevModel; }

    //��ȡ�豸�ͺ�
    inline u8 GetModel(void) const { return m_byDevModel; }

    //�����豸����ϵͳ����
    inline void SetOsType(EMFileSrvOSType emOsType)
    { m_byDevOsType = static_cast<u8>(emOsType); }

    //��ȡ����ϵͳ����
    inline EMFileSrvOSType GetOsType(void) const
    { return static_cast<EMFileSrvOSType>(m_byDevOsType); }

    //ת���ַ���
    void ToString(s8 szType[MAX_FILESRV_DEVSTRING_LEN]) const
    {
        memset( szType, '_', MAX_FILESRV_DEVSTRING_LEN - 1 );
        szType[MAX_FILESRV_DEVSTRING_LEN - 1] = '\0';
        switch ( m_byDevType )
        {
        case enumFileSrvDevTypeMT:
            memcpy( szType, "mt", 2 );
            break;
        case enumFileSrvDevTypeFileSrv:
            memcpy( szType, "sus", 3 );
            break;
        case enumFileSrvDevTypeClient:
            memcpy( szType, "suc", 3 );
            break;
        default:
            break;
        }
        switch ( m_byDevModel )
        {
        case enumFileSrvDevModelMTTS6610:
            memcpy( szType + FILESRV_DEVSTRING_MODEL_BEGIN, "TS6610", 6 );
            break;
        case enumFileSrvDevModelMTTS5210:
            memcpy( szType + FILESRV_DEVSTRING_MODEL_BEGIN, "TS5210", 6 );
            break;
        case enumFileSrvDevModelMTV5:
            memcpy( szType + FILESRV_DEVSTRING_MODEL_BEGIN, "V5", 2 );
            break;
        case enumFileSrvDevModelMTTS3210:
            memcpy( szType + FILESRV_DEVSTRING_MODEL_BEGIN, "TS3210", 6 );
            break;
        case enumFileSrvDevModelMTTS6610E:
            memcpy( szType + FILESRV_DEVSTRING_MODEL_BEGIN, "TS6610E", 7 );
            break;
        case enumFileSrvDevModelMTTS6210:
            memcpy( szType + FILESRV_DEVSTRING_MODEL_BEGIN, "TS6210", 6 );
            break;
        case enumFileSrvDevModelMTTS6210E:
            memcpy( szType + FILESRV_DEVSTRING_MODEL_BEGIN, "TS6210E", 7 );
            break;
		case enumFileSrvDevModelMTTS5610:
            memcpy( szType + FILESRV_DEVSTRING_MODEL_BEGIN, "TS5610", 6 );
            break;
		case enumFileSrvDevModelMTTS3610:
            memcpy( szType + FILESRV_DEVSTRING_MODEL_BEGIN, "TS3610", 6 );
            break;
		case enumFileSrvDevModelMTKDV7910:
            memcpy( szType + FILESRV_DEVSTRING_MODEL_BEGIN, "KDV7910", 7 );
            break;
		case enumFileSrvDevModelMTKDV7810:
            memcpy( szType + FILESRV_DEVSTRING_MODEL_BEGIN, "KDV7810", 7 );
            break;
        default:
            break;
        }
        switch ( m_byDevOsType )
        {
        case enumFileSrvOSTypeVxworksRaw:
            memcpy( szType + FILESRV_DEVSTRING_OS_BEGIN, "Vxworks Raw", 11 );
            break;
        case enumFileSrvOsTypeVxworksTffs:
            memcpy( szType + FILESRV_DEVSTRING_OS_BEGIN, "Vxworks Tffs", 12 );
            break;
        case enumFileSrvOsTypeWindows:
            memcpy( szType + FILESRV_DEVSTRING_OS_BEGIN, "Windows", 7 );
            break;
        case enumFileSrvOsTypeLinuxPowerPC:
            memcpy( szType + FILESRV_DEVSTRING_OS_BEGIN, "Linux PowerPC", 13 );
            break;
        case enumFileSrvOsTypeLinuxDavinci:
            memcpy( szType + FILESRV_DEVSTRING_OS_BEGIN, "Linux ARM", 9 );
            break;
        default:
            break;
        }
    }

    //���ַ�����ȡ
    BOOL32 FromString(s8 szType[MAX_FILESRV_DEVSTRING_LEN])
    {
        if ( strlen( szType ) != MAX_FILESRV_DEVSTRING_LEN - 1 )
            return FALSE;

        if ( memcmp( szType, "mt", 2 ) == 0 )
            m_byDevType = enumFileSrvDevTypeMT;
        else if ( memcmp( szType, "sus", 3 ) == 0 )
            m_byDevType = enumFileSrvDevTypeFileSrv;
        else if ( memcmp( szType, "suc", 3 ) == 0 )
            m_byDevType = enumFileSrvDevTypeClient;
        else
            m_byDevType = enumFileSrvDevTypeUnknown;

        if ( memcmp( szType + FILESRV_DEVSTRING_MODEL_BEGIN, "TS6610E", 7 ) == 0 )
            m_byDevModel = enumFileSrvDevModelMTTS6610E;
        else if ( memcmp( szType + FILESRV_DEVSTRING_MODEL_BEGIN, "TS5210", 6 ) == 0 )
            m_byDevModel = enumFileSrvDevModelMTTS5210;
        else if ( memcmp( szType + FILESRV_DEVSTRING_MODEL_BEGIN, "V5", 2 ) == 0 )
            m_byDevModel = enumFileSrvDevModelMTV5;
        else if ( memcmp( szType + FILESRV_DEVSTRING_MODEL_BEGIN, "TS3210", 6 ) == 0 )
            m_byDevModel = enumFileSrvDevModelMTTS3210;
        else if ( memcmp( szType + FILESRV_DEVSTRING_MODEL_BEGIN, "TS6610", 6 ) == 0 )
            m_byDevModel = enumFileSrvDevModelMTTS6610;
		// 6210Eһ��Ҫ����6210ǰ�ж�
        else if ( memcmp( szType + FILESRV_DEVSTRING_MODEL_BEGIN, "TS6210E", 7 ) == 0 )
            m_byDevModel = enumFileSrvDevModelMTTS6210E;
        else if ( memcmp( szType + FILESRV_DEVSTRING_MODEL_BEGIN, "TS6210", 6 ) == 0 )
            m_byDevModel = enumFileSrvDevModelMTTS6210;

		else if ( memcmp( szType + FILESRV_DEVSTRING_MODEL_BEGIN, "TS5610", 6 ) == 0 )
			m_byDevModel = enumFileSrvDevModelMTTS5610;
		else if ( memcmp( szType + FILESRV_DEVSTRING_MODEL_BEGIN, "TS3610", 6 ) == 0 )
			m_byDevModel = enumFileSrvDevModelMTTS3610;
		else if ( memcmp( szType + FILESRV_DEVSTRING_MODEL_BEGIN, "KDV7910", 7 ) == 0 )
			m_byDevModel = enumFileSrvDevModelMTKDV7910;
		else if ( memcmp( szType + FILESRV_DEVSTRING_MODEL_BEGIN, "KDV7810", 7 ) == 0 )
			m_byDevModel = enumFileSrvDevModelMTKDV7810;

        else
            m_byDevModel = enumFileSrvDevModelMTUnknown;

        if ( memcmp( szType + FILESRV_DEVSTRING_OS_BEGIN, "Vxworks Raw", 11 ) == 0 )
            m_byDevOsType = enumFileSrvOSTypeVxworksRaw;
        else if ( memcmp( szType + FILESRV_DEVSTRING_OS_BEGIN, "Vxworks Tffs", 12 ) == 0 )
            m_byDevOsType = enumFileSrvOsTypeVxworksTffs;
        else if ( memcmp( szType + FILESRV_DEVSTRING_OS_BEGIN, "Windows", 7 ) == 0 )
            m_byDevOsType = enumFileSrvOsTypeWindows;
        else if ( memcmp( szType + FILESRV_DEVSTRING_OS_BEGIN, "Linux PowerPC", 13 ) == 0 )
            m_byDevOsType = enumFileSrvOsTypeLinuxPowerPC;
        else if ( memcmp( szType + FILESRV_DEVSTRING_OS_BEGIN, "Linux ARM", 9 ) == 0 )
            m_byDevOsType = enumFileSrvOsTypeLinuxDavinci;
        else
            m_byDevOsType = enumFileSrvOSTypeUnknown;

        return TRUE;
    }

private:
    u8      m_byDevType;                //�豸����(EMFileSrvDevType)
    u8      m_byDevModel;               //�豸�ͺ�(EMFileSrvDevMTMode)
    u8      m_byDevOsType;              //�豸����ϵͳ����(EMFileSrvOSType)
    u8      m_byReserved1;              //�����ֶ�
}
#ifndef WIN32
__attribute__ ( (packed) )
#endif//WIN32
IFCSrvDev
;

//�ļ�������Ϣ
typedef struct tagFCSrvFileInfo//len: 72
{
public:
    tagFCSrvFileInfo() : m_dwFileType(0), m_dwFileSize(0)
    { SetNull(); }

    //�ÿ�
    inline void SetNull(void) { memset( this, 0, sizeof (tagFCSrvFileInfo) ); }

    //�����ļ�����
    inline void SetFileType(EMFileSrvFileType emFileType)
    { m_dwFileType = htonl( static_cast<u32>(emFileType) ); }

    //��ȡ�ļ�����
    inline EMFileSrvFileType GetFileType(void) const
    { return static_cast<EMFileSrvFileType>( ntohl( m_dwFileType ) ); }

    //�����ļ���С
    inline void SetFileSize(u32 dwFileSize) { m_dwFileSize = htonl(dwFileSize); }

    //��ȡ�ļ���С
    inline u32 GetFileSize(void) const { return ntohl(m_dwFileSize); }

    //�����ļ���
    inline void SetFileName(LPCSTR lptrFileName)
    {
        memset( m_szFileName, 0, sizeof (m_szFileName) );
        if ( lptrFileName != NULL )
        {
            strncpy( m_szFileName, lptrFileName, sizeof (m_szFileName) - 1 );
        }
    }

    //��ȡ�ļ���
    inline LPCSTR GetFileName(void) const { return m_szFileName; }

private:
    u32     m_dwFileType;       //�ļ�����(EMFileSrvFileType)
    u32     m_dwFileSize;       //�ļ���С(���ֽڼ���)
    s8      m_szFileName[MAX_FILESRV_FILENAME_LEN];//�ļ���
}
#ifndef WIN32
__attribute__ ( (packed) )
#endif//WIN32
IFCSrvFileInfo
;

//�豸�汾������Ϣ
typedef struct tagFCSrvDevVerInfo//len: 856
{
public:
    tagFCSrvDevVerInfo() : m_byFileNum(0)
    { SetNull(); }

    //�ÿ�
    inline void SetNull(void)
    { memset( this, 0, sizeof (tagFCSrvDevVerInfo) ); }

    //�����豸
    inline void SetDev(const IFCSrvDev &tDev) { m_tDev = tDev; }

    //��ȡ�豸
    inline IFCSrvDev GetDev(void) const { return m_tDev; }

    //����Ӳ���汾��
    inline void SetHardwareVer(const IFCHardwareVer &tHardVer)
    { m_tHardVer = tHardVer; }

    //��ȡӲ���汾��
    inline IFCHardwareVer GetHardwareVer(void) const { return m_tHardVer; }

    //��������汾��
    inline void SetSoftwareVer(const IFCSoftwareVer &tSoftVer)
    { m_tSoftVer = tSoftVer; }

    //��ȡ����汾��
    inline IFCSoftwareVer GetSoftwareVer(void) const { return m_tSoftVer; }

    //�����޸���������
    inline void SetBugReport(LPCSTR lptrBugReport)
    {
        memset( m_aszBugReport, 0, sizeof (m_aszBugReport) );
        if ( lptrBugReport != NULL )
        {
            strncpy( m_aszBugReport, lptrBugReport,
                     sizeof (m_aszBugReport) - 1 );
        }
    }

    //��ȡ�޸�����
    inline LPCSTR GetBugReport(void) const { return m_aszBugReport; }

    //����ļ�
    BOOL32 AddOneFile(EMFileSrvFileType emFileType, u32 dwFileSize,
                      LPCSTR lptrFileName)
    {
        if ( m_byFileNum >= MAX_FILESRV_DEVFILE_NUM || lptrFileName == NULL
             || dwFileSize == 0 )//��������
        {
            return FALSE;
        }
        for ( u8 byIndex = 0; byIndex < m_byFileNum; byIndex ++ )//�ļ������Ѵ���
        {
            if ( m_atFileInfo[byIndex].GetFileType() == emFileType )
            {
                return FALSE;
            }
        }

        m_atFileInfo[m_byFileNum].SetFileType( emFileType );
        m_atFileInfo[m_byFileNum].SetFileSize( dwFileSize );
        m_atFileInfo[m_byFileNum].SetFileName( lptrFileName );
        m_byFileNum ++;
        return TRUE;
    }

    //�޸��ļ�
    BOOL32 EditOneFile(EMFileSrvFileType emFileType, u32 dwFileSize,
                       LPCSTR lptrFileName)
    {
        if ( m_byFileNum == 0 || lptrFileName == NULL || dwFileSize == 0 )//��������
        {
            return FALSE;
        }
        for ( u8 byIndex = 0; byIndex < m_byFileNum; byIndex ++ )
        {
            if ( m_atFileInfo[byIndex].GetFileType() == emFileType )//�ļ������Ѵ���
            {
                m_atFileInfo[byIndex].SetFileSize( dwFileSize );
                m_atFileInfo[byIndex].SetFileName( lptrFileName );
                return TRUE;
            }
        }
        return FALSE;
    }

    //ɾ���ļ�
    BOOL32 DelOneFile(EMFileSrvFileType emFileType)
    {
        for ( u8 byIndex = 0; byIndex < m_byFileNum; byIndex ++ )
        {
            if ( m_atFileInfo[byIndex].GetFileType() == emFileType )//�ļ������Ѵ���
            {
                if ( byIndex < MAX_FILESRV_DEVFILE_NUM - 1 )
                {
                    memmove( m_atFileInfo + byIndex, m_atFileInfo + byIndex + 1,
                             (MAX_FILESRV_DEVFILE_NUM - byIndex - 1)
                                    * sizeof (IFCSrvFileInfo) );
                }
                m_atFileInfo[MAX_FILESRV_DEVFILE_NUM - 1].SetNull();
                m_byFileNum --;
                return TRUE;
            }
        }
        return FALSE;
    }
    BOOL32 DelOneFile(s32 nIndex)
    {
        if ( nIndex < static_cast<s32>(m_byFileNum) )
        {
            if ( nIndex < MAX_FILESRV_DEVFILE_NUM - 1 )
            {
                memmove( m_atFileInfo + nIndex, m_atFileInfo + nIndex + 1,
                         (MAX_FILESRV_DEVFILE_NUM - nIndex - 1)
                                    * sizeof (IFCSrvFileInfo) );
            }
            m_atFileInfo[MAX_FILESRV_DEVFILE_NUM - 1].SetNull();
            m_byFileNum --;
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    } 

    //����б�
    inline void ClearFileList(void)
    {
        memset( m_atFileInfo, 0, sizeof (m_atFileInfo) );
        m_byFileNum = 0;
    }

    //��ȡ�ļ�����
    inline s32 GetFileNum(void) const
    { return static_cast<s32>(m_byFileNum); }

    //��ȡһ���ļ�
    inline IFCSrvFileInfo GetOneFile(s32 nIndex) const
    {
        if ( nIndex < static_cast<s32>(m_byFileNum) )
        {
            return m_atFileInfo[nIndex];
        }
        else
        {
            IFCSrvFileInfo tInfo;
            return tInfo;
        }
    }

    //ָ�����͵��ļ��Ƿ����
    inline BOOL32 IsFileExist(EMFileSrvFileType emFileType)
    {
        for ( u8 byIndex = 0; byIndex < m_byFileNum; byIndex ++ )
        {
            if ( m_atFileInfo[byIndex].GetFileType() == emFileType )
            {
                return TRUE;
            }
        }
        return FALSE;
    }

private:
    IFCSrvDev       m_tDev;             //�豸
    IFCHardwareVer  m_tHardVer;         //Ӳ���汾��
    IFCSoftwareVer  m_tSoftVer;         //����汾��
    s8              m_aszBugReport[MAX_FILESRV_BUG_REPORT_LEN];//�ļ��޸���Ϣ����
    u8              m_byFileNum;        //���豸�汾��Ҫ���ļ��ܸ���
    u8              m_abyReserved1[3];  //�����ֶ�
    IFCSrvFileInfo  m_atFileInfo[MAX_FILESRV_DEVFILE_NUM];//�ļ���Ϣ
}
//#ifndef WIN32
//__attribute__ ( (packed) )
//#endif//WIN32
IFCSrvDevVerInfo
;

//�ļ�������Ϣ
typedef struct tagFCSrvFileFullInfo : public tagFCSrvFileInfo//len: 76
{
public:
    tagFCSrvFileFullInfo() : m_dwFileNo(0)
    { SetNull(); }

    //�ÿ�
    inline void SetNull(void)
    { memset( this, 0, sizeof (tagFCSrvFileFullInfo) ); }

    //�����ļ����
    inline void SetFileNo(u32 dwFileNo)
    { m_dwFileNo = htonl( dwFileNo ); }

    //��ȡ�ļ����
    inline u32 GetFileNo(void) const
    { return ntohl( m_dwFileNo ); }

private:
    u32     m_dwFileNo;         //�ļ����
}
#ifndef WIN32
__attribute__ ( (packed) )
#endif//WIN32
IFCSrvFileFullInfo
;

//�豸�汾������Ϣ
//�豸�汾������Ϣ
typedef struct tagFCSrvDevVerFullInfo//len: 876
{
public:
    tagFCSrvDevVerFullInfo() : m_dwDevNo(0), m_byFileNum(0), m_byRecommend(0)
    { SetNull(); }

    //�ÿ�
    inline void SetNull(void)
    { memset( this, 0, sizeof (tagFCSrvDevVerFullInfo) ); }

    //���ñ��
    inline void SetDevNo(u32 dwDevNo)
    { m_dwDevNo = htonl( dwDevNo ); }

    //��ȡ���
    inline u32 GetDevNo(void) const
    { return ntohl( m_dwDevNo ); }

    //�����豸
    inline void SetDev(const IFCSrvDev &tDev) { m_tDev = tDev; }

    //��ȡ�豸
    inline const IFCSrvDev& GetDev(void) const { return m_tDev; }

    //����Ӳ���汾��
    inline void SetHardwareVer(const IFCHardwareVer &tHardVer)
    { m_tHardVer = tHardVer; }

    //��ȡӲ���汾��
    inline IFCHardwareVer GetHardwareVer(void) const { return m_tHardVer; }

    //��������汾��
    inline void SetSoftwareVer(const IFCSoftwareVer &tSoftVer)
    { m_tSoftVer = tSoftVer; }

    //��ȡ����汾��
    inline IFCSoftwareVer GetSoftwareVer(void) const { return m_tSoftVer; }

    //�����޸���������
    inline void SetBugReport(LPCSTR lptrBugReport)
    {
        memset( m_aszBugReport, 0, sizeof (m_aszBugReport) );
        if ( lptrBugReport != NULL )
        {
            strncpy( m_aszBugReport, lptrBugReport,
                     sizeof (m_aszBugReport) - 1 );
        }
    }

    //��ȡ�޸�����
    inline LPCSTR GetBugReport(void) const { return m_aszBugReport; }

    //�����Ƿ��Ƽ�
    inline void SetRecommend(BOOL32 bRecommend)
    { m_byRecommend = bRecommend ? 1 : 0; }

    //��ȡ�Ƿ��Ƽ�
    inline BOOL32 IsRecommend(void) const
    { return (m_byRecommend == 1 ? TRUE : FALSE); }

    //����ļ�
    BOOL32 AddOneFile(u32 dwFileNo, EMFileSrvFileType emFileType,
                      u32 dwFileSize, LPCSTR lptrFileName)
    {
        if ( m_byFileNum >= MAX_FILESRV_DEVFILE_NUM || lptrFileName == NULL
             || dwFileSize == 0 )//��������
        {
            return FALSE;
        }
        for ( u8 byIndex = 0; byIndex < m_byFileNum; byIndex ++ )//�ļ������Ѵ���
        {
            if ( m_atFileInfo[byIndex].GetFileType() == emFileType )
            {
                return FALSE;
            }
        }

        m_atFileInfo[m_byFileNum].SetFileNo( dwFileNo );
        m_atFileInfo[m_byFileNum].SetFileType( emFileType );
        m_atFileInfo[m_byFileNum].SetFileSize( dwFileSize );
        m_atFileInfo[m_byFileNum].SetFileName( lptrFileName );
        m_byFileNum ++;
        return TRUE;
    }

    //�޸��ļ�
    BOOL32 EditOneFile(u32 dwFileNo, EMFileSrvFileType emFileType,
                       u32 dwFileSize, LPCSTR lptrFileName)
    {
        if ( m_byFileNum == 0 || lptrFileName == NULL || dwFileSize == 0 )//��������
        {
            return FALSE;
        }
        for ( u8 byIndex = 0; byIndex < m_byFileNum; byIndex ++ )
        {
            if ( m_atFileInfo[byIndex].GetFileType() == emFileType )//�ļ������Ѵ���
            {
                m_atFileInfo[byIndex].SetFileNo( dwFileNo );
                m_atFileInfo[byIndex].SetFileSize( dwFileSize );
                m_atFileInfo[byIndex].SetFileName( lptrFileName );
                return TRUE;
            }
        }
        return FALSE;
    }

    //ɾ���ļ�
    BOOL32 DelOneFile(EMFileSrvFileType emFileType)
    {
        for ( u8 byIndex = 0; byIndex < m_byFileNum; byIndex ++ )
        {
            if ( m_atFileInfo[byIndex].GetFileType() == emFileType )//�ļ������Ѵ���
            {
                if ( byIndex < MAX_FILESRV_DEVFILE_NUM - 1 )
                {
                    memmove( m_atFileInfo + byIndex, m_atFileInfo + byIndex + 1,
                             (MAX_FILESRV_DEVFILE_NUM - byIndex - 1)
                                    * sizeof (IFCSrvFileFullInfo) );
                }
                m_atFileInfo[MAX_FILESRV_DEVFILE_NUM - 1].SetNull();
                m_byFileNum --;
                return TRUE;
            }
        }
        return FALSE;
    }
    BOOL32 DelOneFile(s32 nIndex)
    {
        if ( nIndex < static_cast<s32>(m_byFileNum) )
        {
            if ( nIndex < MAX_FILESRV_DEVFILE_NUM - 1 )
            {
                memmove( m_atFileInfo + nIndex, m_atFileInfo + nIndex + 1,
                         (MAX_FILESRV_DEVFILE_NUM - nIndex - 1)
                                    * sizeof (IFCSrvFileFullInfo) );
            }
            m_atFileInfo[MAX_FILESRV_DEVFILE_NUM - 1].SetNull();
            m_byFileNum --;
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    } 

    //����б�
    inline void ClearFileList(void)
    {
        memset( m_atFileInfo, 0, sizeof (m_atFileInfo) );
        m_byFileNum = 0;
    }

    //��ȡ�ļ�����
    inline s32 GetFileNum(void) const
    { return static_cast<s32>(m_byFileNum); }

    //��ȡһ���ļ�
    inline IFCSrvFileFullInfo GetOneFile(s32 nIndex) const
    {
        if ( nIndex < static_cast<s32>(m_byFileNum) )
        {
            return m_atFileInfo[nIndex];
        }
        else
        {
            IFCSrvFileFullInfo tInfo;
            return tInfo;
        }
    }

    //ָ�����͵��ļ��Ƿ����
    inline BOOL32 IsFileExist(EMFileSrvFileType emFileType)
    {
        for ( u8 byIndex = 0; byIndex < m_byFileNum; byIndex ++ )
        {
            if ( m_atFileInfo[byIndex].GetFileType() == emFileType )
            {
                return TRUE;
            }
        }
        return FALSE;
    }

private:
    u32             m_dwDevNo;          //�豸���
    IFCSrvDev       m_tDev;             //�豸
    IFCHardwareVer  m_tHardVer;         //Ӳ���汾��
    IFCSoftwareVer  m_tSoftVer;         //����汾��
    s8              m_aszBugReport[MAX_FILESRV_BUG_REPORT_LEN];//�ļ��޸���Ϣ����
    u8              m_byFileNum;        //���豸�汾��Ҫ���ļ��ܸ���
    u8              m_byRecommend;      //�ð汾�Ƿ�Ϊ�Ƽ��汾
    u8              m_abyReserved1[2];  //�����ֶ�
    IFCSrvFileFullInfo  m_atFileInfo[MAX_FILESRV_DEVFILE_NUM];//�ļ���Ϣ
}
//#ifndef WIN32
//__attribute__ ( (packed) )
//#endif//WIN32
IFCSrvDevVerFullInfo
;

//��־��ѯ�ṹ
typedef struct tagLogReqInfo//len: 64
{
public:
    tagLogReqInfo() { SetNull(); }

    //�ÿ�
    inline void SetNull(void) { memset( this, 0, sizeof (tagLogReqInfo) ); }

    //����������
    inline void SetMainType(EMFileSrvLogReqMainType emType)
    { m_byMainType = static_cast<u8>(emType); }

    //��ȡ������
    inline EMFileSrvLogReqMainType GetMainType(void) const
    { return static_cast<EMFileSrvLogReqMainType>(m_byMainType); }

    //������־����������
    inline void SetSubType(EMFileSrvLogReqSubTypeCategory emType)
    { m_wSubTypeCategory = htons( static_cast<u16>(emType) ); }

    //��ȡ��־����������
    inline EMFileSrvLogReqSubTypeCategory GetCategorySubType(void) const
    { return static_cast<EMFileSrvLogReqSubTypeCategory>(ntohs(m_wSubTypeCategory)); }

    //������־����������
    inline void SetSubType(EMFileSrvLogReqSubTypeLevel emType)
    { m_wSubTypeLevel = htons( static_cast<u16>(emType) ); }

    //��ȡ��־����������
    inline EMFileSrvLogReqSubTypeLevel GetLevelSubType(void) const
    { return static_cast<EMFileSrvLogReqSubTypeLevel>(ntohs(m_wSubTypeLevel)); }

    //����ʱ��������
    inline void SetSubType(EMFileSrvLogReqSubTypeTime emType)
    { m_wSubTypeTime = htons( static_cast<u16>(emType) ); }

    //��ȡʱ��������
    inline EMFileSrvLogReqSubTypeTime GetTimeSubType(void) const
    { return static_cast<EMFileSrvLogReqSubTypeTime>(ntohs(m_wSubTypeTime)); }

    //�����豸������
    inline void SetSubType(EMFileSrvLogReqSubTypeDev emType)
    { m_wSubTypeDev = htons( static_cast<u16>(emType) ); }

    //��ȡ�豸������
    inline EMFileSrvLogReqSubTypeDev GetDevSubType(void) const
    { return static_cast<EMFileSrvLogReqSubTypeDev>(ntohs(m_wSubTypeDev)); }

    //���ò������������
    inline void SetSubType(EMFileSrvLogReqSubTypeResult emType)
    { m_wSubTypeResult = htons( static_cast<u16>(emType) ); }

    //��ȡ�������������
    inline EMFileSrvLogReqSubTypeResult GetResultSubType(void) const
    { return static_cast<EMFileSrvLogReqSubTypeResult>(ntohs(m_wSubTypeResult)); }

    //�����¼�������
    inline void SetSubType(EMFileSrvLogReqSubTypeEvent emType)
    { m_wSubTypeEvent = htons( static_cast<u16>(emType) ); }

    //��ȡ�¼�������
    inline EMFileSrvLogReqSubTypeEvent GetEventSubType(void) const
    { return static_cast<EMFileSrvLogReqSubTypeEvent>(ntohs(m_wSubTypeEvent)); }

    //�����¼������������豸����
    inline void SetEventSubType(EMFileSrvLogReqEventSubTypeDevOpr emType)
    { m_wSubTypeEventSubTypeDevOpr = htons( static_cast<u16>(emType) ); }

    //��ȡ�¼������������豸����
    inline EMFileSrvLogReqEventSubTypeDevOpr GetEventSubTypeDevOpr(void) const
    { return static_cast<EMFileSrvLogReqEventSubTypeDevOpr>(
                        ntohs(m_wSubTypeEventSubTypeDevOpr) ); }

    //�����¼����������Ϳͻ��˲���
    inline void SetEventSubType(EMFileSrvLogReqEventSubTypeClientOpr emType)
    { m_wSubTypeEventSubTypeClientOpr = htons( static_cast<u16>(emType) ); }

    //��ȡ�¼����������Ϳͻ��˲���
    inline EMFileSrvLogReqEventSubTypeClientOpr GetEventSubTypeClientOpr(void) const
    { return static_cast<EMFileSrvLogReqEventSubTypeClientOpr>(
                        ntohs(m_wSubTypeEventSubTypeClientOpr) ); }

    //�����豸
    inline void SetDev(const IFCSrvDev &tDev) { m_tDev = tDev; }

    //��ȡ�豸
    inline IFCSrvDev GetDev(void) const { return m_tDev; }

    //����Ӳ���汾��
    inline void SetHardwareVer(const IFCHardwareVer &tHardVer)
    { m_tHardVer = tHardVer; }

    //��ȡӲ���汾��
    inline IFCHardwareVer GetHardwareVer(void) const { return m_tHardVer; }

    //������ʼʱ��(��������ʱ��)
    inline void SetStartTime(time_t dwTime) { m_dwStartTime = htonl( dwTime ); }

    //��ȡ��ʼʱ��
    inline time_t GetStartTime(void) const { return ntohl( m_dwStartTime ); }

    //���ý���ʱ��(��������ʱ��)
    inline void SetEndTime(time_t dwTime) { m_dwEndTime = htonl( dwTime ); }

    //��ȡ����ʱ��
    inline time_t GetEndTime(void) const { return ntohl( m_dwEndTime ); }

private:
    u8          m_byMainType;       //������(EMFileSrvLogReqMainType������������ | ����)
    u8          m_byReserved1;
    u16         m_wReserved2;
    u16         m_wSubTypeCategory; //������(EMFileSrvLogReqSubTypeCategory������������ | ����)
    u16         m_wSubTypeLevel;    //������(EMFileSrvLogReqSubTypeLevel������������ | ����)
    u16         m_wSubTypeTime;     //������(EMFileSrvLogReqSubTypeTime������������ | ����)
    u16         m_wSubTypeDev;      //������(EMFileSrvLogReqSubTypeDev������������ | ����)
    u16         m_wSubTypeResult;   //������(EMFileSrvLogReqSubTypeResult������������ | ����)
    u16         m_wSubTypeEvent;    //������(EMFileSrvLogReqSubTypeEvent������������ | ����)
    u16         m_wSubTypeEventSubTypeDevOpr;   //������(EMFileSrvLogReqEventSubTypeDevOpr������������ | ����)
    u16         m_wSubTypeEventSubTypeClientOpr;//������(EMFileSrvLogReqEventSubTypeClientOpr������������ | ����)
    IFCSrvDev           m_tDev;         //ָ���豸
    IFCHardwareVer      m_tHardVer;     //Ӳ���汾��
    time_t      m_dwStartTime;   //ָ����ʼʱ��(��������ʱ��)
    time_t      m_dwEndTime;     //ָ������ʱ��(��������ʱ��)
}
#ifndef WIN32
__attribute__ ( (packed) )
#endif//WIN32
ILogReqInfo
;

//��־��ѯ���
typedef struct tagLogRetInfo//len: 120
{
public:
    tagLogRetInfo() : m_dwSerialID(0), m_wCategory(0), m_wLevel(0),
                      m_wEvent(0), m_wEventSubType(0), m_dwTime(0),
                      m_dwErrCode(0)
    { memset( m_abyReserved, 0, sizeof (m_abyReserved) ); }

    //�ÿ�
    inline void SetNull(void) { memset( this, 0, sizeof (tagLogRetInfo) ); }

    //�������к�
    inline void SetSerialNo(u32 dwSN) { m_dwSerialID = htonl( dwSN ); }

    //��ȡ���к�
    inline u32 GetSerialNo(void) const { return ntohl( m_dwSerialID ); }

    //������־����
    inline void SetCategory(EMFileSrvLogReqSubTypeCategory emType)
    { m_wCategory = htons( static_cast<u16>(emType) ); }

    //��ȡ��־����
    inline EMFileSrvLogReqSubTypeCategory GetCategory(void) const
    { return static_cast<EMFileSrvLogReqSubTypeCategory>(ntohs(m_wCategory)); }

    //������־����
    inline void SetLevel(EMFileSrvLogReqSubTypeLevel emType)
    { m_wLevel = htons( static_cast<u16>(emType) ); }

    //��ȡ��־����
    inline EMFileSrvLogReqSubTypeLevel GetLevel(void) const
    { return static_cast<EMFileSrvLogReqSubTypeLevel>(ntohs(m_wLevel)); }

    //�����¼�����
    inline void SetEvent(EMFileSrvLogReqSubTypeEvent emType)
    { m_wEvent = htons( static_cast<u16>(emType) ); }

    //��ȡ�¼�����
    inline EMFileSrvLogReqSubTypeEvent GetEvent(void) const
    { return static_cast<EMFileSrvLogReqSubTypeEvent>(ntohs(m_wEvent)); }

    //�����¼�����������
    inline void SetEventSubType(u16 wType) { m_wEventSubType = htons(wType); }

    //��ȡ�¼�����������
    inline u16 GetEventSubType(void) const { return ntohs( m_wEventSubType ); }

    //�����豸
    inline void SetDev(const IFCSrvDev &tDev) { m_tDev = tDev; }

    //��ȡ�豸
    inline IFCSrvDev GetDev(void) const { return m_tDev; }

    //����Ӳ���汾��
    inline void SetHardwareVer(const IFCHardwareVer &tVer) { m_tHardVer = tVer; }

    //��ȡӲ���汾��
    inline IFCHardwareVer GetHardwareVer(void) const { return m_tHardVer; }

    //����ʱ��(��������ʱ��)
    inline void SetTime(time_t dwTime) { m_dwTime = htonl( dwTime ); }

    //��ȡʱ��(��������ʱ��)
    inline time_t GetTime(void) const { return ntohl( m_dwTime ); }

    //���ô�����
    inline void SetErrorCode(u32 dwErrorCode) { m_dwErrCode = htonl(dwErrorCode); }

    //��ȡ������
    inline u32 GetErrorCode(void) const { return ntohl( m_dwErrCode ); }

private:
    u32         m_dwSerialID;   //��־�����ݿ��д洢�����к�
    u16         m_wCategory;    //��־����(EMFileSrvLogReqSubTypeCategory)
    u16         m_wLevel;       //��־�ȼ�(EMFileSrvLogReqSubTypeLevel)
    u16         m_wEvent;       //�¼�(EMFileSrvLogReqSubTypeEvent)
    u16         m_wEventSubType;//�¼�������(EMFileSrvLogReqEventSubTypeDevOpr/ EMFileSrvLogReqEventSubTypeClientOpr)
    IFCSrvDev   m_tDev;         //�豸
    IFCHardwareVer  m_tHardVer; //Ӳ���汾��
    time_t      m_dwTime;       //ʱ��(��������ʱ��)
    u32         m_dwErrCode;    //���������
    s8          m_abyReserved[64];  //����ֵ(�û�����ʱΪ�������û������汾����ʱΪ���º�İ汾��)
}
#ifndef WIN32
__attribute__ ( (packed) )
#endif//WIN32
ILogRetInfo
;


//���ݿ�������Ϣ
typedef struct tagFCSrcDBConfig//len: 184
{
public:
    tagFCSrcDBConfig() : m_wDBPort(0), m_byReserved1(0)
    { SetNull(); }

    //�ÿ�
    inline void SetNull(void)
    { memset( this, 0, sizeof (tagFCSrcDBConfig) ); }

    //��������
    inline void SetName(LPCSTR lptrName)
    {
        memset( m_szDBName, 0, sizeof (m_szDBName) );
        if ( lptrName != NULL )
        {
            strncpy( m_szDBName, lptrName, sizeof (m_szDBName) - 1 );
        }
    }

    //��ȡ����
    inline LPCSTR GetName(void) const { return m_szDBName; }

    //����IP
    inline void SetIP(u32 dwIP)
    {
        u8 *pbyBuf = reinterpret_cast<u8*>(&dwIP);
        sprintf( m_szDBIP, "%d.%d.%d.%d%c", pbyBuf[3], pbyBuf[2], pbyBuf[1],
                 pbyBuf[0], 0 );
    }

    //����IP
    void SetIP(LPCSTR lptrIP)
    {
        memset( m_szDBIP, 0, sizeof (m_szDBIP) );
        if ( lptrIP != NULL )
        {
            strncpy( m_szDBIP, lptrIP, sizeof (m_szDBIP) - 1 );
        }
    }

    //��ȡIP
    inline LPCSTR GetIP(void) const { return m_szDBIP; }

    //���ö˿�
    inline void SetPort(u16 wPort) { m_wDBPort = htons( wPort ); }

    //��ȡ�˿�
    inline u16 GetPort(void) const { return ntohs( m_wDBPort ); }

    //��������
    inline void SetEngineType(EMDBEngineType emType)
    { m_byDBEngineType = static_cast<u8>(emType); }

    //��ȡ����
    inline EMDBEngineType GetEngineType(void) const
    { return static_cast<EMDBEngineType>(m_byDBEngineType); }

    //�����û�
    inline void SetUser(LPCSTR lptrUsername, LPCSTR lptrPwd)
    {
        memset( m_szDBUsername, 0, sizeof (m_szDBUsername) );
        memset( m_szDBUserPwd, 0, sizeof (m_szDBUserPwd) );
        if ( lptrUsername != NULL )
        {
            strncpy( m_szDBUsername, lptrUsername, sizeof (m_szDBUsername) - 1 );
        }
        if ( lptrPwd != NULL )
        {
            strncpy( m_szDBUserPwd, lptrPwd, sizeof (m_szDBUserPwd) - 1 );
        }
    }

    //��ȡ�û���
    inline LPCSTR GetUsername(void) const { return m_szDBUsername; }

    //��ȡ����
    inline LPCSTR GetPassword(void) const { return m_szDBUserPwd; }

private:
    s8  m_szDBName[MAX_DB_NAME_LEN];        //���ݿ�����
    s8  m_szDBIP[20];                       //���ݿ�����IP�ִ�
    u16 m_wDBPort;                          //���ݿ����Ӷ˿�
    u8  m_byDBEngineType;                   //���ݿ���������
    u8  m_byReserved1;
    s8  m_szDBUsername[MAX_DB_USERNAME_LEN];//���ݿ������û���
    s8  m_szDBUserPwd[MAX_DB_USER_PWD_LEN]; //���ݿ���������
}
#ifndef WIN32
__attribute__ ( (packed) )
#endif//WIN32
IFCSrvDBConfig
;


//����������
typedef struct tagFCSrvConfig//len: 8
{
    tagFCSrvConfig() : m_dwListenIP(0), m_wTelnetPort(0), m_wListenPort(0)
    {}

    //�ÿ�
    inline void SetNull(void) { memset( this, 0, sizeof (tagFCSrvConfig) ); }

    //��������IP
    void SetListenIP(u32 dwIP) { m_dwListenIP = htonl( dwIP ); }

    //��ȡ����IP
    u32 GetListenIP(void) const { return ntohl( m_dwListenIP ); }

    //���������˿�
    void SetLitenPort(u16 wPort) { m_wListenPort = htons( wPort ); }

    //��ȡ�����˿�
    u16 GetListenPort(void) const { return ntohs( m_wListenPort ); }

    //���õ��Զ˿�
    void SetTelnetPort(u16 wPort) { m_wTelnetPort = htons( wPort ); }

    //��ȡ���Զ˿�
    u16 GetTelnetPort(void) const { return ntohs( m_wTelnetPort ); }

private:
    u32     m_dwListenIP;   //����IP
    u16     m_wListenPort;  //�����˿�
    u16     m_wTelnetPort;  //���Զ˿�
}
#ifndef WIN32
__attribute__ ( (packed) )
#endif//WIN32
IFCSrvConfig
;

//�ļ���������
typedef struct tagFCSrvFileConfig//len: 328
{
public:
    tagFCSrvFileConfig() : m_dwFTPIP(0), m_wFTPPort(SUS_FTP_DEFAULT_PORT)
    { SetNull(); }

    //�ÿ�
    inline void SetNull(void) { memset( this, 0, sizeof (tagFCSrvFileConfig) ); }

//    //����FTP IP��ַ
//    inline void SetFtpIP(u32 dwIP) { m_dwFTPIP = htonl( dwIP ); }
//
//    //��ȡFTP IP��ַ
//    inline u32 GetFtpIP(void) const { return ntohl( m_dwFTPIP ); }
//
//    //����FTP �˿�
//    inline void SetFtpPort(u16 wPort) { m_wFTPPort = htons( wPort ); }
//
//    //��ȡFTP �˿�
//    inline u16 GetFtpPort(void) const { return ntohs( m_wFTPPort ); }
//
//    //����FTP ·��
//    inline void SetFtpPath(LPCSTR lptrPath)
//    {
//        memset( m_szFtpPath, 0, sizeof (m_szFtpPath) );
//        strncpy( m_szFtpPath, lptrPath, sizeof (m_szFtpPath) - 1 );
//    }
//
//    //��ȡFTP ·��
//    inline LPCSTR GetFtpPath(void) const { return m_szFtpPath; }
//
//    //����FTP �û���
//    void SetFtpUser(LPCSTR lptrUsername, LPCSTR lptrPwd)
//    {
//        memset( m_szFtpUser, 0, sizeof (m_szFtpUser) );
//        if ( lptrUsername != NULL )
//        {
//            strncpy( m_szFtpUser, lptrUsername, sizeof (m_szFtpUser) - 1 );
//        }
//    }
//
//    //��ȡFTP �û���
//    inline LPCSTR GetFtpUser(void) const { return m_szFtpUser; }
//
//    //����FTP ����
//    void SetFtpPassword(LPCSTR lptrPwd)
//    {
//        memset( m_szFtpPwd, 0, sizeof (m_szFtpPwd) );
//        if ( lptrPwd != NULL )
//        {
//            strncpy( m_szFtpPwd, lptrPwd, sizeof (m_szFtpPwd) - 1 );
//        }
//    }
//
//    //��ȡFTP ����
//    inline LPCSTR GetFtpPassword(void) const { return m_szFtpPwd; }

    //���ñ��ش��·��
    void SetLocalPath(LPCSTR lptrPath)
    {
        memset( m_szLocalPath, 0, sizeof (m_szLocalPath) );
        if ( lptrPath != NULL )
        {
            strncpy( m_szLocalPath, lptrPath, sizeof (m_szLocalPath) - 1 );
        }
    }

    //��ȡ���ش��·��
    inline LPCSTR GetLocalPath(void) const { return m_szLocalPath; }

private:
    u32 m_dwFTPIP;                              //FTP IP��ַ
    u16 m_wFTPPort;                             //FTP �˿�
    u16 m_wReserved1;
    s8  m_szFtpPath[MAX_SUS_FTP_PATH_LEN];      //FTP·��
    s8  m_szFtpUser[MAX_SUS_FTP_USERNAME_LEN];  //FTP�û���
    s8  m_szFtpPwd[MAX_SUS_FTP_PASSWORD_LEN];   //FTP����
    s8  m_szLocalPath[MAX_SUS_LOCAL_FILE_PATH]; //�����ļ�·��
}
#ifndef WIN32
__attribute__ ( (packed) )
#endif//WIN32
IFCSrvFileConfig
;

//���Ź�����������
typedef struct tagFCSrvWdSrv//len: 8
{
public:
    tagFCSrvWdSrv() : m_wServerPort(0), m_byCheckCount(0), m_wCheckTime(0)
    { SetNull(); }

    //�ÿ�
    inline void SetNull(void)
    { memset( this, 0, sizeof (tagFCSrvWdSrv) ); }

    //���ö˿�
    inline void SetPort(u16 wPort) { m_wServerPort = htons( wPort ); }

    //��ȡ�˿�
    inline u16 GetPort(void) const { return ntohs( m_wServerPort ); }

    //���ö���������
    inline void SetCheckCount(u8 byCount) { m_byCheckCount = byCount; }

    //��ȡ����������
    inline u8 GetCheckCount(void) const { return m_byCheckCount; }

    //���ö������ʱ��
    inline void SetCheckTime(u16 wTime) { m_wCheckTime = htons( wTime ); }

    //��ȡ�������ʱ��
    inline u16 GetCheckTime(void) const { return ntohs( m_wCheckTime ); }

private:
    u16     m_wServerPort;      //���Ź��������˿�
    u8      m_byCheckCount;     //���Ź�����������������
    u8      m_byReserved1;
    u16     m_wCheckTime;       //���Ź��������������ʱ��
    u16     m_wReserved2;
}
#ifndef WIN32
__attribute__ ( (packed) )
#endif//WIN32
IFCSrvWdSrv
;

//���Ź��ͻ�������
typedef struct tagFCSrvWdAgt//len: 8
{
public:
    tagFCSrvWdAgt() : m_dwCheckCount(0), m_dwRegTime(0) {}

    //�ÿ�
    inline void SetNull(void) { memset( this, 0, sizeof (tagFCSrvWdAgt) ); }

    //���ö������ʱ��
    inline void SetCheckCount(u32 dwCount) { m_dwCheckCount = htonl( dwCount ); }

    //��ȡ�������ʱ��
    inline u32 GetCheckCount(void) const { return ntohl( m_dwCheckCount ); }

    //����ע��ʱ��
    inline void SetRegTime(u32 dwTime) { m_dwRegTime = htonl( dwTime ); }

    //��ȡע��ʱ��
    inline u32 GetRegTime(void) const { return ntohl( m_dwRegTime ); }

private:
    u32     m_dwCheckCount; //���Ź��ͻ��˶���������
    u32     m_dwRegTime;    //���Ź��ͻ���ע��ʱ����
}
#ifndef WIN32
__attribute__ ( (packed) )
#endif//WIN32
IFCSrvWdAgt
;

typedef struct tagFCSrvWdConfig//len: 20
{
public:
    tagFCSrvWdConfig() : m_byNeedStart(0) {}

    //�ÿ�
    inline void SetNull(void)
    {
        m_byNeedStart = 0;
        m_tSrv.SetNull();
        m_tAgt.SetNull();
    }

    //�����Ƿ���Ҫ����
    inline void SetNeedStart(BOOL32 bNeedStart)
    { m_byNeedStart = bNeedStart ? 1 : 0; }

    //�ж��Ƿ���Ҫ����
    inline BOOL32 IsNeedStart(void) const
    { return ( m_byNeedStart == 1 ? TRUE : FALSE ); }

private:
    u8      m_byNeedStart;
    u8      m_abyReserved1[3];
public:
    IFCSrvWdSrv  m_tSrv;
    IFCSrvWdAgt  m_tAgt;
}
#ifndef WIN32
__attribute__ ( (packed) )
#endif//WIN32
IFCSrvWdConfig
;

typedef struct tagFCSrvThreadConfig//len: 12
{
public:
    tagFCSrvThreadConfig() : m_dwSUCDBConnNum(htonl(SUS_DB_SUC_CONNNUM)),
                             m_dwSUSDBConnNum(htonl(SUS_DB_SUS_CONNNUM)),
                             m_dwMTDBConnNum(htonl(SUS_DB_MT_CONNNUM)) {}

    //�ÿ�
    inline void SetNull(void)
    {
        m_dwSUCDBConnNum = htonl( SUS_DB_SUC_CONNNUM );
        m_dwSUSDBConnNum = htonl( SUS_DB_SUS_CONNNUM );
        m_dwMTDBConnNum = htonl( SUS_DB_MT_CONNNUM );
    }

//    inline void SetSucDbNum(u32 dwNum) { m_dwSUCDBConnNum = htonl( dwNum ); }

    inline u32 GetSucDbNum(void) const { return ntohl( m_dwSUCDBConnNum ); }

//    inline void SetSusDbNum(u32 dwNum) { m_dwSUSDBConnNum = htonl( dwNum ); }

    inline u32 GetSusDbNum(void) const { return ntohl( m_dwSUSDBConnNum ); }

//    inline void SetMtDbNum(u32 dwNum) { m_dwMTDBConnNum = htonl( dwNum ); }

    inline u32 GetMtDbNum(void) const { return ntohl( m_dwMTDBConnNum ); }

private:
    u32     m_dwSUCDBConnNum;   //�ͻ������ݿ������̸߳���
    u32     m_dwSUSDBConnNum;   //���������ݿ������̸߳���
    u32     m_dwMTDBConnNum;    //�ն����ݿ������̸߳���
}
#ifndef WIN32
__attribute__ ( (packed) )
#endif//WIN32
IFCSrvThreadConfig
;

//������ȫ������
typedef struct tagSusConfig//len: 8 + 184 + 328 + 20
{
public:
    tagSusConfig() {}

    //�ÿ�
    void SetNull(void)
    {
        m_tSrvCfg.SetNull();
        m_tDbConnCfg.SetNull();
        m_tFileCfg.SetNull();
        m_tWdCfg.SetNull();
        m_tThreadCfg.SetNull();
    }

public:
    IFCSrvConfig        m_tSrvCfg;      //����������
    IFCSrvDBConfig      m_tDbConnCfg;   //���ݿ���������
    IFCSrvFileConfig    m_tFileCfg;     //�ļ�����
    IFCSrvWdConfig      m_tWdCfg;       //���Ź�����
    IFCSrvThreadConfig  m_tThreadCfg;   //�߳�����
}
#ifndef WIN32
__attribute__ ( (packed) )
#endif//WIN32
ISusConfig
;

/*------------------------------------------------------------------------------
  ��������Ϣ�ṹ
------------------------------------------------------------------------------*/
//��Ϣ���ͽṹ(ǧ��Ҫ��գ������Ҳ����汾��)
typedef struct tagFCFileSrvMsg//len: 28 * 1024
{
public:
    tagFCFileSrvMsg(const u8 *pbyMsgBody = NULL, u16 wMsgBodyLen = 0)
                    : m_dwServiceNo(0), m_dwSrcVer(FILESRV_CUR_VERSION),
                      m_dwSerialNo(0), m_dwErrorCode(0), m_wTotalPkt(0),
                      m_wCurPkt(0), m_wMsgLen(0)
    { SetMsgBody( pbyMsgBody, wMsgBodyLen ); }

    //���÷����
    inline void SetServiceNo(u32 dwServiceNo)
    { m_dwServiceNo = htonl(dwServiceNo); }

    //��ȡ�����
    inline u32 GetServiceNo(void) const { return ntohl( m_dwServiceNo ); }

    //���ð汾��(������ר��)
    inline void SetSrcVer(void) { m_dwSrcVer = htonl( FILESRV_CUR_VERSION ); }

    //��ȡ�汾��
    inline u32 GetSrcVer(void) const { return ntohl( m_dwSrcVer ); }

    //������Ϣ���к�
    inline void SetSN(u32 dwSN) { m_dwSerialNo = htonl( dwSN ); }

    //��ȡ��Ϣ���к�
    inline u32 GetSN(void) const { return ntohl( m_dwSerialNo ); }

    //���ô�����
    inline void SetErrorCode(u32 dwErrorCode)
    { m_dwErrorCode = htonl( dwErrorCode ); }

    //��ȡ������
    inline u32 GetErrorCode(void) const { return ntohl( m_dwErrorCode ); }

    //�����ܰ���
    inline void SetTotalPkt(u16 wPkt) { m_wTotalPkt = htons( wPkt ); }

    //��ȡ�ܰ���
    inline u32 GetTotalPkt(void) const { return ntohs( m_wTotalPkt ); }

    //���õ�ǰ����
    inline void SetCurPkt(u16 wPkt) { m_wCurPkt = htons( wPkt ); }

    //��ȡ��ǰ����
    inline u16 GetCurPkt(void) const { return ntohs( m_wCurPkt ); }

    //������Ϣ��
    inline void SetMsgBody(const u8 *pbyMsgBody = NULL, u16 wMsgBodyLen = 0)
    {
        SetSrcVer();
        m_wMsgLen = 0;
        memset( m_abyMsgBody, 0, sizeof (m_abyMsgBody) );
        if ( pbyMsgBody != NULL && wMsgBodyLen > 0 )
        {
            m_wMsgLen = min( wMsgBodyLen, static_cast<u16>(MAX_FILESRV_MSG_LEN) );
            memcpy( m_abyMsgBody, pbyMsgBody, m_wMsgLen );
            m_wMsgLen = htons( m_wMsgLen );
        }
    }

    //�������õ���Ϣ��β��ƴ����Ϣ��
    inline void CatMsgBody(const u8 *pbyMsgBody = NULL, u16 wMsgBodyLen = 0)
    {
        if ( pbyMsgBody != NULL && wMsgBodyLen > 0 )
        {
            u16 wCurLen = ntohs( m_wMsgLen );//��ǰ�Ѵ������Ϣ�峤��
            //����׷�ӵ���Ϣ�峤��
            u16 wThisLen = min( wMsgBodyLen,
                                static_cast<u16>(MAX_FILESRV_MSG_LEN - wCurLen) );
            memcpy( m_abyMsgBody + wCurLen, pbyMsgBody, wThisLen );
            m_wMsgLen = htons( wCurLen + wThisLen );
        }
    }

    //��ȡ��Ϣ���峤��
    inline u16 GetBodyLen(void) const { return ntohs( m_wMsgLen ); }

    //��ȡ��Ϣ������
    inline const u8* GetMsgBody(void) const { return m_abyMsgBody; }

    //����OSP��Ϣ��ȡ������Ϣ����
    inline u16 GetSrvMsgLen(void) const 
    { return ntohs( m_wMsgLen ) + MAX_FILESRV_MSG_HEAD_LEN; }

    //����OSP��Ϣ��ȡ������Ϣ�ṹָ��
    inline const u8 *GetSrvMsg(void) const
    { return reinterpret_cast<const u8*>(this); }

private:
    u32         m_dwServiceNo;      //*_LOGIN_ACK������ķ���ţ�Req��Ϣ������д
    u32         m_dwSrcVer;         //��Ϣ��Դ�汾�ţ�����Ҫ��д
    u32         m_dwSerialNo;       //��ˮ�ţ�Server��͸��ת������Ҫ������Ϣͬ������(�ն˲�ÿ��һ��REQ���Զ�+1����ô��Ӧ��ACK���к�һ��)
    u32         m_dwErrorCode;      //�����룬NACK��Ϣ��Ҫ������GetFileSrvErrorStr��ȡ����
    u16         m_wTotalPkt;        //�ļ������ܰ���(�����ļ�)
    u16         m_wCurPkt;          //�ļ����䵱ǰ����(�����ļ�)
    u16         m_wMsgLen;          //��Ϣ�峤��
    u8          m_abyResrved[18];   //�����ֶ�
    u8          m_abyMsgBody[MAX_FILESRV_MSG_LEN];  //��Ϣ��
}
#ifndef WIN32
__attribute__ ( (packed) )
#endif//WIN32
IFCFileSrvMsg
;


#ifdef WIN32
#pragma pack( pop )
#endif//WIN32


#endif//_FILESRVCLIENTSTRUCT_H
