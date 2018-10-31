/******************************************************************************
ģ����      ��Sap
�ļ���      ��Sap.h
����ļ�    ��Sap.cpp
�ļ�ʵ�ֹ��ܣ�ʵ��Sap
����        ������
�汾        ��4.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �߶���      �޸�����
23/05/05    4.0         ����        ����        ����
******************************************************************************/
#ifndef _SAP_H_
#define _SAP_H_

#ifdef WIN32
#pragma warning (disable : 4786)
#endif
//#include "StdAfx.h"
#include <map>
#include <list>
#include <algorithm>
#include <kdvtype.h>
#include <ptlib.h>



/*====================================================================
// ��ӡ��־ �궨��
=====================================================================*/
#ifdef ENABLE_SAP_LOG
    static PMutex G_SAP_LOG;
    #define SAP_LOG(format, para1, para2, para3) \
        { \
            PWaitAndSignal lock(G_SAP_LOG); \
            printf(format, para1, para2, para3); \
            printf("\n"); \
        }
/*
        { \
            CHAR anBuf[1024]; \
	        sprintf(anBuf, ".\\T120_LOG\\%ld_%ld.log", GetCurrentProcessId(), GetCurrentThreadId()); \
            HANDLE handleFile = CreateFile(anBuf, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); \
            if (handleFile != NULL) \
            { \
                SetFilePointer(handleFile, NULL, NULL, FILE_END); \
                DWORD dwRcv; \
                SYSTEMTIME tSystime; \
                GetLocalTime(&tSystime); \
                CHAR anFormat[256]; \
                sprintf(anFormat, "[%2.2d:%2.2d:%2.2d:%3.3d] SAP    : %s\r\n", tSystime.wHour, tSystime.wMinute, tSystime.wSecond, tSystime.wMilliseconds, format); \
                sprintf(anBuf, anFormat, para1, para2, para3); \
                WriteFile(handleFile, anBuf, strlen(anBuf), &dwRcv, NULL); \
                CloseHandle(handleFile); \
            } \
        }
*/
#else
    #define SAP_LOG(format, para1, para2, para3)
#endif



#ifndef NEW_WITH_CHECK
    #ifdef ENABLE_NEW_CHECK
        static PMutex G_NEW_CHECK_LOG;
        #define CHECK_NEW(pNewPoint) \
            if (pNewPoint == NULL) \
            { \
                PWaitAndSignal lock(G_NEW_CHECK_LOG); \
                printf("**** ���ش���:�����ڴ�ʧ��**** \n"); \
            }
        #define CHECK_DELETE(pDeletePoint) \
            if (pDeletePoint == NULL) \
            { \
                PWaitAndSignal lock(G_NEW_CHECK_LOG); \
                printf("**** ���ش���:ɾ���ڴ�ʧ��**** \n"); \
            }
    #else
        #define CHECK_NEW(pNewPoint)
        #define CHECK_DELETE(pDeletePoint)
    #endif

    #define NEW_WITH_CHECK(pcNewPoint, NewTypeAndParas) \
        pcNewPoint = new NewTypeAndParas; \
        CHECK_NEW(pcNewPoint);
    #define DECLEAR_AND_NEW(CType, pcNewPoint, NewTypeAndParas) \
        CType* pcNewPoint = new NewTypeAndParas; \
        CHECK_NEW(pcNewPoint);
    #define DELETE_WITH_CHECK(pcDeletePoint) \
        CHECK_DELETE(pcDeletePoint); \
        delete pcDeletePoint;
    #define DELETE_ARRAY_WITH_CHECK(paDeleteArray) \
        CHECK_DELETE(paDeleteArray); \
        delete[] paDeleteArray;
#endif



/*====================================================================
���� �� CResource
���� �� Sap�������Դ
====================================================================*/
class CResource
{
public:
    virtual void OnAccess(void* pReqData, void* pAckData) = 0;
};

/*====================================================================
���� �� CSap
���� �� Sap������
====================================================================*/
class CSap
{
private:
    // ������Դ��<��Դָ��,������>
    typedef std::map<CResource*, PMutex> TResourceMap;
    TResourceMap m_mapRes;
    // m_mapRes�Ļ�����
    PMutex m_mutexRes;

    // ���еȴ��еķ��ʣ�<�������Դ,��Դ�ȴ�����> 
    typedef std::list<PSemaphore*> TSemaphoreList;
    typedef std::map<CResource*, TSemaphoreList> TWaitMap;
    TWaitMap m_mapWait;
    // m_mapWait�Ļ�����
    PMutex m_mutexWait;

public:
    // ���캯��
    CSap();
    // ��������
    virtual ~CSap(){};
    // �����Դ
    bool IncludeRes(CResource* pcIncludeRes);
    // �Ƴ���Դ
    bool ExcludeRes(CResource* pcExcludeRes);
    // ������Դ������ָ����Դ�ķ���Ȩ
    bool AccessRes(CResource* pcAccessRes, void* pReqData, void* pAckData);
    // �õ�ָ����Դ�ķ���Ȩǰ���ȵ��øú���
    virtual void On_Pre_AccessRes(CResource* pcCreateRes, void* pReqData) = 0;

private:

    // �ڲ��������
    typedef enum
    {
        e_NoSuchRes,
        e_Fail,
        e_Success,
        e_Unexpect
    } TSapResult;

    // ����Դ����
//    TSapResult LockRes(CResource* pcOperateRes);
    TSapResult LockRes(CResource* pcOperateRes, PSemaphore*& pThreadWaitSema);

    // ����Դ��ɢ
    TSapResult UnlockRes(CResource* pcOperateRes);
    // ����ȴ��ź���
    PSemaphore* NewThreadSema(CResource* pcOperateRes);
    // ɾ���ȴ��ź���
    TSapResult DeleteThreadSema(CResource* pcOperateRes, PSemaphore* pThreadWaitSema);
    // �̵߳ȴ��ź���
    TSapResult WaitThreadSema(CResource* pcOperateRes, PSemaphore* pThreadWaitSema);
    // �ͷŵȴ��ź���
    TSapResult ReleaseOneThreadSema(CResource* pcOperateRes);

    // ����Դ��Exclude������Access����
    bool OperateRes(CResource* pcOperateRes, bool bType, void* pReqData);
};

#endif
