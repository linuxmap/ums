/******************************************************************************
ģ����      ��GccSap
�ļ���      ��GccSap.h
����ļ�    ��GccSap.cpp
�ļ�ʵ�ֹ��ܣ�ʵ��GccSap
����        ������
�汾        ��4.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �߶���      �޸�����
24/05/05    4.0         ����        ����        ����
******************************************************************************/
#ifndef _GCC_SAP_H_
#define _GCC_SAP_H_

#include <mcssap.h>
#include <gccprimitives.h>


/*====================================================================
// ��ӡ��־ �궨��
=====================================================================*/
#ifdef ENABLE_GCC_LOG
    static PMutex G_GCC_LOG;
    #define GCC_LOG(format, para1, para2, para3) \
        { \
            PWaitAndSignal lock(G_GCC_LOG); \
            printf("GCC__LOG:  "); \
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
                sprintf(anFormat, "[%2.2d:%2.2d:%2.2d:%3.3d] GCC    : %s\r\n", tSystime.wHour, tSystime.wMinute, tSystime.wSecond, tSystime.wMilliseconds, format); \
                sprintf(anBuf, anFormat, para1, para2, para3); \
                WriteFile(handleFile, anBuf, strlen(anBuf), &dwRcv, NULL); \
                CloseHandle(handleFile); \
            } \
        }
*/
#else
    #define GCC_LOG(format, para1, para2, para3)
#endif


// Gcc�ڲ��߳���������
#ifdef GCC_THREAD
    #define GCC_THREAD_NUM GCC_THREAD
#else
    #define GCC_THREAD_NUM 3
#endif


class CGccThread;
class CGccProvider;
class CGccConference;

/*====================================================================
���� �� CGccSap
���� �� GccSap������
====================================================================*/
class CGccSap : public CSap, public CMqmSyncReceiver
{
private:
    // CMcsSap����
    CMcsSap m_cMcsSap;
    // CMqm����ָ��
    CMqmInterface* m_pcMqmInterface;
    // McsProvider������Դ
    TMessageContext m_tMcsProvider;
    // GccProvider������Դ
    TMessageContext m_tGccProvider;
    // CGccThread�߳�����
    CGccThread* m_apGccThread[GCC_THREAD_NUM];
    // ���ж�ȡ�����ź���
    PMutex m_mutexQueue;
    // CGccProvider����
    CGccProvider* m_pcGccProvider;
    // CGccDomainָ���б�
    typedef std::list<CMcsDomain*> TConferenceList;
    TConferenceList m_listGccConference;

public:
    // ���캯��
    CGccSap(NodeType enumNodeType, PString strNodeName, PString strNodeEmail, PString strNodePhone, PString strNodeLocation);
    // ��������
    ~CGccSap();
    // ������Դ������ָ����Դ�ķ���Ȩ
    void On_Pre_AccessRes(CResource* pcAccessRes, void* pReqData){};
    // ͬ����Ϣ������
    virtual bool OnRecvSyncMsg(const CMsg& cSendMsg, CMsg& cRecvMsg);
    // �õ�MQM
    CMqmInterface* GetMqmInterface();
    // �õ�GccProvider������Դ
    const TMessageContext& GetGccQueue();
    // �õ�McsProvider������Դ
    const TMessageContext GetMcsQueue();

};

// Gcc�����߻����ߵ�����
typedef enum
{
    // Provider
    e_GccProvider,
    // Conference
    e_GccConference
} TGccReceiverType;

#endif
