/******************************************************************************
ģ����      ��McsSap
�ļ���      ��McsSap.h
����ļ�    ��McsSap.cpp
�ļ�ʵ�ֹ��ܣ�ʵ��McsSap
����        ������
�汾        ��4.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �߶���      �޸�����
24/05/05    4.0         ����        ����        ����
******************************************************************************/
#ifndef _MCS_SAP_H_
#define _MCS_SAP_H_

#include <sap.h>
#include "mqminterface.h"
#include <mcsprimitives.h>


/*====================================================================
// ��ӡ��־ �궨��
=====================================================================*/
#ifdef ENABLE_MCS_LOG
    static PMutex G_MCS_LOG;
    #define MCS_LOG(format, para1, para2, para3) \
        { \
            PWaitAndSignal lock(G_MCS_LOG); \
            printf("MCS__LOG:  "); \
            printf(format, para1, para2, para3); \
            printf("\n"); \
        }
/*
        { \
            char anBuf[1024]; \
	        sprintf(anBuf, ".\\T120_LOG\\%ld_%ld.log", GetCurrentProcessId(), GetCurrentThreadId()); \
            HANDLE handleFile = CreateFile(anBuf, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); \
            if (handleFile != NULL) \
            { \
                SetFilePointer(handleFile, NULL, NULL, FILE_END); \
                DWORD dwRcv; \
                SYSTEMTIME tSystime; \
                GetLocalTime(&tSystime); \
                char anFormat[256]; \
                sprintf(anFormat, "[%2.2d:%2.2d:%2.2d:%3.3d] MCS    : %s\r\n", tSystime.wHour, tSystime.wMinute, tSystime.wSecond, tSystime.wMilliseconds, format); \
                sprintf(anBuf, anFormat, para1, para2, para3); \
                WriteFile(handleFile, anBuf, strlen(anBuf), &dwRcv, NULL); \
                CloseHandle(handleFile); \
            } \
        }
*/
#else
    #define MCS_LOG(format, para1, para2, para3)
#endif

// Mcs�ڲ��߳���������
#ifdef MCS_THREAD
    #define MCS_THREAD_NUM MCS_THREAD
#else
    #define MCS_THREAD_NUM 3
#endif

//class CMcsThread;
class CMcsProvider;
class CMcsDomain;
class CTcAgent;
class CConnectionManager;
/*====================================================================
���� �� CMcsSap
���� �� McsSap������
====================================================================*/
class CMcsSap : public CSap, public CMqmSyncReceiver
{
private:
    // CMqm����
    CMqmInterface m_cMqmInterface;
    // McsProvder������Դ
    TMessageContext m_tMcsProvider;
    // ���ж�ȡ�����ź���
    PMutex m_mutexQueue;
    // CMcsProvider����
    CMcsProvider* m_pcMcsProvider;
    // CMcsDomainָ���б�
    typedef std::list<CMcsDomain*> TDomainList;
    TDomainList m_listMcsDomain;
    // �����ȡ�Ļ�����
    PMutex m_mutexReadQueue;
    //ConnectionManger����
    CConnectionManager *m_pcConnectionManager;
public:
    // ���캯��
    CMcsSap();
    // ���캯��
    ~CMcsSap();
    // ������Դ������ָ����Դ�ķ���Ȩ
    void On_Pre_AccessRes(CResource* pcAccessRes, void* pReqData);
    // ͬ����Ϣ������
    virtual bool OnRecvSyncMsg(const CMsg& cSendMsg, CMsg& cRecvMsg);
    // �õ�MQM Interface
    CMqmInterface* GetMqmInterface();
    // �õ�����ָ�� 
    const TMessageContext& GetMcsQueue();
    CMcsProvider* GetMcsProvider();
    // ����ConnectionManager�����������繦��
    bool StartConnectionManager(const PString& strAddress);
    //�õ�CMcsConnectionManagerָ��
    CConnectionManager* GetConnectionManager();
};


// Mcs�����߻����ߵ�����
typedef enum
{
    // Provider
    e_McsProvider,
    // Conference
    e_McsDomain
} TMcsReceiverType;


#endif
