/*=======================================================================
ģ����      : �ļ�����������
�ļ���      : filesrvdevstruct.h
����ļ�    : ��
�ļ�ʵ�ֹ���: �����������豸�ṹ����
����        : ���
�汾        : V1.0  Copyright(C) 2006-2007 KDC, All rights reserved.
-------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2006/12/28  1.0     ���    ����
=======================================================================*/

#ifndef _FILESRVDEVSTRUCT_H
#define _FILESRVDEVSTRUCT_H

#ifdef WIN32
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#endif//WIN32

#include <ctype.h>
#include <kdvtype.h>
#include <stdio.h>
#include "filesrvconst.h"
#include "filesrvstruct.h"

#ifdef WIN32
    #pragma pack( push )
    #pragma pack( 1 )
    #define window( x )	x
#else
    #include <netinet/in.h>
    #define window( x )
#endif//WIN32

/*------------------------------------------------------------------------------
  ���������豸�����ṹ
------------------------------------------------------------------------------*/
//����汾�ṹ(�ն˵���IDevSoftwareVer)
typedef struct tagDevSoftwareVer1//len: 16
{
public:
    tagDevSoftwareVer1() : m_wMainVer(0), m_wSubVer(0), m_wInterfaceVer(0),
                           m_wModifyVer(0), m_dwDate(0), m_dwReserved1(0)
    {}

    tagDevSoftwareVer1(u16 wMainVer, u16 wSubVer, u16 wIntVer, u16 wModVer,
                       u32 dwDate) : m_dwReserved1(0)
    {
        m_wMainVer      = htons( wMainVer );
        m_wSubVer       = htons( wSubVer );
        m_wInterfaceVer = htons( wIntVer );
        m_wModifyVer    = htons( wModVer );
        m_dwDate        = htonl( dwDate );
    }

    tagDevSoftwareVer1(LPSTR lptrVer) : m_dwReserved1(0)
    { FromString( lptrVer ); }

    //�ÿ�
    inline void SetNull(void) { memset( this, 0, sizeof (tagDevSoftwareVer1) ); }

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
    inline void SetModifyVer(u16 wModifyVer) { m_wModifyVer = htons( wModifyVer ); }

    //��ȡ�޸İ汾��
    inline u16 GetModifyVer(void) const { return ntohs( m_wModifyVer ); }

    //��������
    inline void SetDate(u32 dwDate) { m_dwDate = htonl( dwDate ); }

    //��ȡ����
    inline u32 GetDate(void) const { return ntohl( m_dwDate ); }

    //�Ƚϰ汾
    inline BOOL32 operator<(const tagDevSoftwareVer1 &tVer)
    {
        return ( memcmp( this, &tVer, sizeof (tagDevSoftwareVer1) ) < 0 );
    }
    inline BOOL32 operator>(const tagDevSoftwareVer1 &tVer)
    {
        return ( memcmp( this, &tVer, sizeof (tagDevSoftwareVer1) ) > 0 );
    }
    inline BOOL32 operator==(const tagDevSoftwareVer1 &tVer)
    {
        return ( memcmp( this, &tVer, sizeof (tagDevSoftwareVer1) ) == 0 );
    }

    //ת���ַ���
    inline void ToString(s8 szVer[MAX_FILESRV_SOFTVER_LEN]) const
    {
        sprintf( szVer, "%.2d.%.2d.%.2d.%.2d.%.6d", ntohs( m_wMainVer ),
                 ntohs( m_wSubVer ), ntohs( m_wInterfaceVer ),
                 ntohs( m_wModifyVer ), ntohl( m_dwDate ) );
        return;
    }

    //���ַ�����ȡ
    inline BOOL32 FromString(LPSTR lptrVer)
    {
        if ( lptrVer == NULL || strlen(lptrVer) != 18 )
        {
            return FALSE;
        }
        m_wMainVer      = htons( atoi( lptrVer ) );
        m_wSubVer       = htons( atoi( lptrVer + 3 ) );
        m_wInterfaceVer = htons( atoi( lptrVer + 6 ) );
        m_wModifyVer    = htons( atoi( lptrVer + 9 ) );
        m_dwDate        = htonl( atoi( lptrVer + 12) );
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
IDevSoftwareVer1
;
typedef IDevSoftwareVer1        IDevSoftwareVer;


//Ӳ���汾�ṹ(�ն˵���IDevHardwareVer)
typedef struct tagDevHardwareVer1//len: 32
{
public:
    tagDevHardwareVer1() { SetNull(); }

    //�ÿ�
    inline void SetNull(void)
    { memset( this, 0, sizeof (tagDevHardwareVer1) ); }

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
IDevHardwareVer1
;
typedef IDevHardwareVer1        IDevHardwareVer;


//�ļ���Ϣ
typedef struct tagDevFileInfo1//len: 72
{
public:
    tagDevFileInfo1() : m_dwFileType(0), m_dwFileSize(0)
    { SetNull(); }

    //�ÿ�
    inline void SetNull(void) { memset( this, 0, sizeof (tagDevFileInfo1) ); }

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
IDevFileInfo1
;
typedef IDevFileInfo1           IDevFileInfo;

//�Ƽ��汾��Ϣ(�ն˵���IDevVerInfo)
typedef struct tagDevVerInfo1//len: 820
{
    tagDevVerInfo1() : m_byFileNum(0) { SetNull(); }

    //�ÿ�
    inline void SetNull(void) { memset( this, 0, sizeof (tagDevVerInfo1) ); }

    //��������
    inline void SetBugReport(LPCSTR lptrBugReport)
    {
        memset( m_szBugReport, 0, sizeof (m_szBugReport) );
        if ( lptrBugReport != NULL )
        {
            strncpy( m_szBugReport, lptrBugReport, sizeof (m_szBugReport) - 1 );
        }
    }

    //��ȡ����
    inline LPCSTR GetBugReport(void) const { return m_szBugReport; }

    //�����Ƽ�����汾�� 
    inline void SetSoftwareVer(const IDevSoftwareVer &tSoftVer)
    { m_tSoftVer = tSoftVer; }

    //��ȡ�Ƽ�����汾��
    inline IDevSoftwareVer GetSoftwareVer(void) const
    { return m_tSoftVer; }

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
                                    * sizeof (IDevFileInfo) );
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
                                    * sizeof (IDevFileInfo) );
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

    //����ļ��б�
    inline void ClearFileList(void)
    {
        memset( m_atFileInfo, 0, sizeof (m_atFileInfo) );
        m_byFileNum = 0;
    }

    //��ȡ�ļ�����
    inline s32 GetFileNum(void) const
    { return static_cast<s32>(m_byFileNum); }

    //��ȡһ���ļ�
    inline IDevFileInfo GetOneFile(s32 nIndex) const
    {
        if ( nIndex < static_cast<s32>(m_byFileNum) )
        {
            return m_atFileInfo[nIndex];
        }
        else
        {
            IDevFileInfo tInfo;
            return tInfo;
        }
    }

private:
    u8              m_byFileNum;                                //�ļ�����
    u8              m_abyReserved1[3];
    s8              m_szBugReport[MAX_FILESRV_BUG_REPORT_LEN];  //�޸�����
    IDevSoftwareVer m_tSoftVer;                                 //�Ƽ�����汾��
    IDevFileInfo    m_atFileInfo[MAX_FILESRV_DEVFILE_NUM];      //�ļ���Ϣ
}
//#ifndef WIN32
//__attribute__ ( (packed) )
//#endif//WIN32
IDevVerInfo1
;
typedef IDevVerInfo1            IDevVerInfo;


//�豸(MCU/MT)ע����Ϣ(�ն˵���IDevLoginInfo)
typedef struct tagDevLoginInfo1//len: 212
{
public:
    tagDevLoginInfo1() : m_byDevType(enumFileSrvDevTypeMT),
    	                 m_byDevModel(enumFileSrvDevModelMTV5),
    	                 m_byOSType(enumFileSrvOsTypeLinuxPowerPC), m_byReserved1(0)
    { SetNull(); }

    //�ÿ�
    inline void SetNull(void)
    {
        memset( this, 0, sizeof (tagDevLoginInfo1) );
        m_byDevType = enumFileSrvDevTypeMT;
    }

    //��ȡ�豸����
    inline EMFileSrvDevType GetDevType(void) const
    { return static_cast<EMFileSrvDevType>(m_byDevType); }

    //�����豸�ͺ�
    inline void SetDevModel(EMFileSrvDevMTModel emModel)
    { m_byDevModel = static_cast<u8>(emModel); }

    //��ȡ�豸�ͺ�
    inline EMFileSrvDevMTModel GetDevModel(void) const
    { return static_cast<EMFileSrvDevMTModel>(m_byDevModel); }

    //���ò���ϵͳ����
    inline void SetOsType(EMFileSrvOSType emOsType)
    { m_byOSType = static_cast<u8>(emOsType); }

    //��ȡ����ϵͳ����
    inline EMFileSrvOSType GetOsType(void) const
    { return static_cast<EMFileSrvOSType>(m_byOSType); }

    //�������к�(�ִ���MAC��ַ)
    inline void SetSerialNo(LPCSTR lptrSN)
    {
        memset( m_szSerialNo, 0, sizeof (m_szSerialNo) );
        if ( lptrSN != NULL )
        {
            strncpy( m_szSerialNo, lptrSN, sizeof (m_szSerialNo) - 1 );
        }
    }

    //��ȡ���к�
    inline LPCSTR GetSerialNo(void) const { return m_szSerialNo; }

    //��������汾��
    inline void SetSoftwareVer(const IDevSoftwareVer &tSoftVer)
    { m_tSoftwareVer = tSoftVer; }

    //��ȡ����汾��
    inline IDevSoftwareVer GetSoftwareVer(void) const { return m_tSoftwareVer; }

    //����Ӳ���汾��
    inline void SetHardwareVer(const IDevHardwareVer &tHardVer)
    { m_tHardwareVer = tHardVer; }

    //��ȡӲ���汾��
    inline IDevHardwareVer GetHardwareVer(void) const { return m_tHardwareVer; }

private:
    u8          m_byDevType;    //�豸����(EMFileSrvDevType)���ն���������
    u8          m_byDevModel;   //�豸�ͺ�(EMFileSrvDevMTMode)
    u8          m_byOSType;     //�豸����ϵͳ����(EMFileSrvOSType)
    u8          m_byReserved1;
    s8          m_szSerialNo[MAX_FILESRV_SERIALNO_LEN]; //���к�(�ִ���MAC��ַ)
    IDevSoftwareVer     m_tSoftwareVer;                 //����汾��
    IDevHardwareVer     m_tHardwareVer;                 //Ӳ���汾��
    u8          m_abyReserved2[32];
}
#ifndef WIN32
__attribute__ ( (packed) )
#endif//WIN32
IDevLoginInfo1
;
typedef IDevLoginInfo1          IDevLoginInfo;


/*------------------------------------------------------------------------------
  ��������Ϣ�ṹ
------------------------------------------------------------------------------*/
//��Ϣ���ͽṹ(ǧ��Ҫ��գ������Ҳ����汾��)
typedef struct tagDevFileSrvMsg//len: 28 * 1024
{
public:
    tagDevFileSrvMsg(const u8 *pbyMsgBody = NULL, u16 wMsgBodyLen = 0)
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
    inline void SetSrcVer(EMFileSrvUsedVersion enumSUSVer) { m_dwSrcVer = htonl(enumSUSVer); }

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
    inline void SetMsgBody(const void *pMsgBody = NULL, u16 wMsgBodyLen = 0)
    {
//         SetSrcVer();
        m_wMsgLen = 0;
        memset( m_abyMsgBody, 0, sizeof (m_abyMsgBody) );
        if ( pMsgBody != NULL && wMsgBodyLen > 0 )
        {
            m_wMsgLen = min( wMsgBodyLen, static_cast<u16>(MAX_FILESRV_MSG_LEN) );
            memcpy( m_abyMsgBody, pMsgBody, m_wMsgLen );
            m_wMsgLen = htons( m_wMsgLen );
        }
    }

    //�������õ���Ϣ��β��ƴ����Ϣ��
    inline void CatMsgBody(const void *pMsgBody = NULL, u16 wMsgBodyLen = 0)
    {
        if ( pMsgBody != NULL && wMsgBodyLen > 0 )
        {
            u16 wCurLen = ntohs( m_wMsgLen );//��ǰ�Ѵ������Ϣ�峤��
            //����׷�ӵ���Ϣ�峤��
            u16 wThisLen = min( wMsgBodyLen,
                                static_cast<u16>(MAX_FILESRV_MSG_LEN - wCurLen) );
            memcpy( m_abyMsgBody + wCurLen, pMsgBody, wThisLen );
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
IDevFileSrvMsg
;



#ifdef WIN32
#pragma pack( pop )
#endif//WIN32


#endif//_FILESRVDEVSTRUCT_H
