/*=======================================================================
ģ����      : �ļ�����������
�ļ���      : filesrvstruct.h
����ļ�    : ��
�ļ�ʵ�ֹ���: ���������ýṹ����
����        : ���
�汾        : V1.0  Copyright(C) 2006-2007 KDC, All rights reserved.
-------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2006/12/28  1.0     ���    ����
=======================================================================*/

#ifndef _FILESRVSTRUCT_H
#define _FILESRVSTRUCT_H

#ifdef WIN32
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#endif//WIN32

#include "filesrvconst.h"
#include "osp.h"

#ifndef IN
#define IN
#endif
#ifndef OUT
#define OUT
#endif

#ifdef WIN32
    #pragma comment( lib, "ws2_32.lib" )
    #pragma pack( push )
    #pragma pack( 1 )
    #define window( x )	x
#else
    #include <netinet/in.h>
    #define window( x )
#endif//WIN32

#ifdef _LINUX_

#ifndef min
#define min(a,b) ((a)>(b)?(b):(a))
#endif
#ifndef max
#define max(a,b) ((a)>(b)?(a):(b))
#endif

#ifndef VOID
#define VOID void 
#endif

#endif//_LINUX_


/*------------------------------------------------------------------------------
  ��ȡ��������
------------------------------------------------------------------------------*/
class CErrorString
{
public:
    CErrorString() {}
    virtual ~CErrorString() {}

    /*=============================================================================
    �� �� ��:MtGetErrorStr
    ��    ��:��ȡ��������
    ��    ��:u32 dwErrCode              [in]    ������
             EMFileSrvLanType emLanType [in]    ��������
             s8 szErrStr[1024]          [out]   ��������
    ע    ��:��
    �� �� ֵ:��ȡ�ɹ�: TURE; ��ȡʧ��: FALSE
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2007/01/11  1.0     ���    ����
    =============================================================================*/
    static BOOL32 MtGetErrorStr(u32 dwErrCode, EMFileSrvLanType emLanType,
                                s8 szErrStr[1024])
    {
#define ONE_TEXT(code, chn, eng)                                        \
case code:                                                              \
    strcpy( szErrStr, emLanType == enumFileSrvLanChinese ? chn : eng ); \
    return TRUE;

        switch ( dwErrCode )
        {
        ONE_TEXT( SUS_ERRORCODE_MAXDBCONNECTION, "���ݿ��Ѵ�����������ƣ�", "Maximum database thread limit!" );
        ONE_TEXT( SUS_ERRORCODE_MTALREADY_CONNECT, "���ն������ӣ�", "The MT had already connected!" );
        ONE_TEXT( SUS_ERRORCODE_MAX_SERVICE_SESSION, "�������Ѵ�����������ƣ���ʱ�޷��ṩ�������Ժ����ԣ�", "The server has reach the capacity limit, please try agin later!");
        ONE_TEXT( SUS_ERRORCODE_TIMEOUT, "������ʱ��", "Operation timed out!" );
        ONE_TEXT( SUS_ERRORCODE_SUS_NOT_PREPARED, "��������δ������ϣ�", "The server is starting, please try again later!" );
        ONE_TEXT( SUS_ERRORCODE_SUS_DBLOADDATA_FAIL, "������ά���У����Ժ����ԣ�", "The server is in maintainance, please try again later!" );
        ONE_TEXT( SUS_ERRORCODE_NO_SUCH_FILE, "������ά���У����Ժ����ԣ�", "The server is in maintainance, please try again later!" );
        ONE_TEXT( SUS_ERRORCODE_NO_SUCH_DEV, "������ά���У����Ժ����ԣ�", "The server is in maintainance, please try again later!" );
        ONE_TEXT( SUS_ERRORCODE_SERVER_VERUPDATE, "������ά���У����Ժ����ԣ�", "The server is in maintainance, please try again later!" );
        ONE_TEXT( SUS_ERRORCODE_MT_ALREADY_NEWEST, "�ն��Ѿ������°汾��������£�", "The MT already running on the newest version, you do not have to update!" );
        ONE_TEXT( SUS_ERRORCODE_EXEC_DB_SQL_FAIL, "���ݿ����ʧ�ܣ�", "The Database operation failed!" );
		// fxh
        ONE_TEXT( SUS_ERRORCODE_DEV_VERTOOMUCH, "���ն��ڷ������а汾���࣬����ɾ��ԭ��ʹ�ð汾�ٵݽ��°汾��", "The MT has too much versions in the server, please delete the old one first, then deliever the new!" );

        default:
            return FALSE;
        }
    }

    /*=============================================================================
    �� �� ��:ClientGetErrorStr
    ��    ��:��ȡ��������
    ��    ��:u32 dwErrCode              [in]    ������
             EMFileSrvLanType emLanType [in]    ��������
             s8 szErrStr[1024]          [out]   ��������
    ע    ��:��
    �� �� ֵ:��ȡ�ɹ�: TURE; ��ȡʧ��: FALSE
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2007/01/11  1.0     ���    ����
    =============================================================================*/
    static BOOL32 ClientGetErrorStr(u32 dwErrCode, EMFileSrvLanType emLanType,
                                    s8 szErrStr[1024])
    {
#define ONE_TEXT(code, chn, eng)                                        \
case code:                                                              \
    strcpy( szErrStr, emLanType == enumFileSrvLanChinese ? chn : eng ); \
    return TRUE;

        switch ( dwErrCode )
        {
        ONE_TEXT( SUS_ERRORCODE_MAXDBCONNECTION, "���ݿ��Ѵ�����������ƣ�", "Maximum database thread limit!" );
        ONE_TEXT( SUS_ERRORCODE_MTALREADY_CONNECT, "���ն������ӣ�", "The MT had already connected!" );
        ONE_TEXT( SUS_ERRORCODE_MAX_SERVICE_SESSION, "�������Ѵ�����������ƣ���ʱ�޷��ṩ�������Ժ����ԣ�", "The server has reach the capacity limit, please try agin later!");
        ONE_TEXT( SUS_ERRORCODE_TIMEOUT, "������ʱ��", "Operation timed out!" );
        ONE_TEXT( SUS_ERRORCODE_SUS_NOT_PREPARED, "��������δ������ϣ�", "The server is starting, please try again later!" );
        ONE_TEXT( SUS_ERRORCODE_SUS_DBLOADDATA_FAIL, "��ʼ����ȡ���ݿ���Ϣʧ�ܣ�", "Load data from DB when starting failed!" );
        ONE_TEXT( SUS_ERRORCODE_NO_SUCH_FILE, "ָ���ļ������ڣ�", "The file does not exist!" );
        ONE_TEXT( SUS_ERRORCODE_NO_SUCH_DEV, "�Ҳ������豸�İ汾��Ϣ��", "can not find version information of the device" );
        ONE_TEXT( SUS_ERRORCODE_MT_ALREADY_NEWEST, "�ն��Ѿ������°汾��������£�", "The MT already running on the newest version, you do not have to update!" );
        ONE_TEXT( SUS_ERRORCODE_LOGIN_INVALID_PWD, "��¼�������", "Invalid login password!" );
        ONE_TEXT( SUS_ERRORCODE_LOGIN_NO_USERNAME, "��¼�û������ڣ�", "Invalid login user!" );
        ONE_TEXT( SUS_ERRORCODE_NO_RIGHT, "�����߱���Ȩ�ޣ�", "You have no right to do that operation!" );
        ONE_TEXT( SUS_ERRORCODE_ADDUSER_EXIST, "��Ҫ��ӵ��û��Ѵ��ڣ�", "The user has already exist that you can not add again!" );
        ONE_TEXT( SUS_ERRORCODE_BUSY_LAST_REQ, "���������ڴ�����һ��������Ϣ��", "The server is busy operating last request!" );
        ONE_TEXT( SUS_ERRORCODE_EDITUSER_NO_EXIST, "��Ҫ�޸ĵ��û��������ڣ�", "The user you want to modify does not exist!" );
        ONE_TEXT( SUS_ERRORCODE_DELUSER_NO_EXIST, "��Ҫɾ�����û��������ڣ�", "The user you want to delete does not exist!" );
        ONE_TEXT( SUS_ERRORCODE_EDITUSER_UP_RIGHT, "����Ȩ�����Լ���Ȩ�ޣ�", "You can not promote your right!" );
        ONE_TEXT( SUS_ERRORCODE_EDITUSER_DW_ADMIN_RT, "����Ȩ�޸ĳ�������ԱȨ�ޣ�", "You can not change the right of the super administrator" );
        ONE_TEXT( SUS_ERRORCODE_EDITUSER_USER_LOGIN, "���û��ѵ�¼���޷��޸���Ȩ�ޣ�", "You can not change the right of the logging user!" );
        ONE_TEXT( SUS_ERRORCODE_EDITUSER_NO_CHG_NAME, "�������޸��û�����", "You can not change the username!" );
        ONE_TEXT( SUS_ERRORCODE_DELUSER_NO_DEL_ADMIN, "����Ȩɾ����������Ա��", "You can not delete the super administrator" );
        ONE_TEXT( SUS_ERRORCODE_DELUSER_USER_LOGIN, "���û��ѵ�¼���޷�ɾ����", "You can not delete the logging user!" );
        ONE_TEXT( SUS_ERRORCODE_EDITVER_NO_DEV, "�Ҳ���ָ���豸��", "Can not find the specified device!" );
        ONE_TEXT( SUS_ERRORCODE_SERVER_VERUPDATE, "���������ڸ��°汾���޷�ִ��ָ��������", "The server is in updating!" );
        ONE_TEXT( SUS_ERRORCODE_SETREC_NO_NEW_FILE, "�µ��Ƽ��汾�ļ�ȱʧ��", "The new recommended file lost!" );
        ONE_TEXT( SUS_ERRORCODE_SETREC_SAME_FILE, "ָ���汾�Ѿ����Ƽ��汾��", "The specified version have been set as recommended already!" );
        ONE_TEXT( SUS_ERRORCODE_NO_MEMORY, "�ڴ治�㣡", "Not enough memory!" );
        ONE_TEXT( SUS_ERRORCODE_DELVER_NO_RECOMMEND, "������ɾ���Ƽ��汾�ļ���", "You have not got the right to delete the recommended version!" );
        ONE_TEXT( SUS_ERRORCODE_DELVER_NO_FILE, "��Ҫɾ���İ汾�����ڣ�", "Can not find the version you want to delete!" );
        ONE_TEXT( SUS_ERRORCODE_EXEC_DB_SQL_FAIL, "���ݿ����ʧ�ܣ�", "The Database operation failed!" );
        ONE_TEXT( SUS_ERRORCODE_UPDATEFILE_IN_DOING, "��һ�ΰ汾������δ�������޷��ٴθ���", "The last updating has in progress, that you can not start a new one now!" );
        ONE_TEXT( SUS_ERRORCODE_UPDATEFILE_VER_EXIST, "�ð汾�Ѵ��ڣ���ɾ���������ϴ���", "The version has already exist, please delete the old one and update again!" );
        ONE_TEXT( SUS_ERRORCODE_DEV_HARDVER_CONFLICT, "����Ӳ���汾���Ѵ��ڣ�", "Part of the specified hardware version had already exist!" );
        ONE_TEXT( SUS_ERRORCODE_UPDATE_LAST_UNFINNISH, "��һ�ļ���δ������ϣ��޷����д˴δ��䣡", "The last file has not finnished receiving yet!" );
        ONE_TEXT( SUS_ERRORCODE_UPDATE_FILE_NOTEXIST, "�˴��ϴ����ļ�����ȱʧ���޷�������", "The specified file does not prepared!" );
        ONE_TEXT( SUS_ERRORCODE_UPDATE_FILEWRITE_FAIL, "�ļ���ʧ�ܣ�", "Failed to open new file!" );
        ONE_TEXT( SUS_ERRORCODE_UPDATE_FILE_TOTALPK, "������ļ��ܰ�����", "Invalid total package number parameter!" );
        ONE_TEXT( SUS_ERRORCODE_UPDATE_FILE_CURPK, "�ļ���ǰ���������ܰ�����", "Invalid current package number!" );
        ONE_TEXT( SUS_ERRORCODE_UPDATE_FILE_PKSIZE, "�ļ����������", "The transferring file package is too large!" );
        ONE_TEXT( SUS_ERRORCODE_UPDATE_FILE_TYPE, "�Ƿ��ļ����ͣ�", "Illegal file type!" );
        ONE_TEXT( SUS_ERRORCODE_UPDATE_FILE_SIZE, "�ļ���С���꣡", "The file size is too large!" );
        ONE_TEXT( SUS_ERRORCODE_UPDATE_FILE_CURPK_SN, "��ǰ�ļ�����Ŵ���", "Invalid current package number!" );
        ONE_TEXT( SUS_ERRORCODE_UPDATE_FILENAME, "�ļ����Ѵ��ڣ�", "The filename had already existed!" );
        ONE_TEXT( SUS_ERRORCODE_UPDATE_FILETYPE, "�ļ������Ѵ��ڣ�", "The file type had already existed!" );
        ONE_TEXT( SUS_ERRORCODE_UPDATE_PACK_SIZE, "��ǰ�������С���Ʋ�����", "The package size is not the same to the real transferring ones!" );
        ONE_TEXT( SUS_ERRORCODE_RESET_MAINTENANCE, "�汾ά���У�������������", "You can not reset the system when the server is in maintenance state!" );
        ONE_TEXT( SUS_ERRORCODE_RESET_MTLOGIN, "��ǰ�����ն˵�¼��������������", "You can not reset the system when some of the MTs in upgrading!" );
		//fxh
		ONE_TEXT( SUS_ERRORCODE_DEV_VERTOOMUCH, "���ն��ڷ������ϰ汾�������������ֵ����ɾ����ʹ�õİ汾�����ϴ���Ҫ���°汾!", "The MT has too much verison in the server, please delete the unused one first!")
		ONE_TEXT( SUS_ERRORCODE_NO_OTHER_VERSION, "��������û�����ø��ն˵��������ð汾!", "There is no other verison available for this type of MT!")
      
		default:
            return FALSE;
        }
    }
};

#ifdef WIN32
#pragma pack( pop )
#endif//WIN32

#endif//_FILESRVSTRUCT_H


